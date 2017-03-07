//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "SendFile_Cpp.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TSendFiles *SendFiles;
//---------------------------------------------------------------------------
__fastcall TSendFiles::TSendFiles(TComponent* Owner)
        : TForm(Owner)
{
FullFileName=new TStringList();//要发送的全路经文件名
FSTimeOut=0;                   //命令超时计数器
BuildTable16(cnCRC_CCITT);     //建立CRC校验表
SleepTime=30;
}
//---------------------------------------------------------------------------


//****************设置文件保存路径******************
void __fastcall TSendFiles::Button5Click(TObject *Sender)
{
  AnsiString Dir0 = "";
  if (SelectDirectory(Dir0, TSelectDirOpts() << sdAllowCreate << sdPerformCreate << sdPrompt,0)) Dir->Text = Dir0;
}
//---------------------------------------------------------------------------


//****************完成设置，返回主画面***************
void __fastcall TSendFiles::Button4Click(TObject *Sender)
{
Notebook1->ActivePage="Main";
}
//---------------------------------------------------------------------------


//****************进入设置画面*******************
void __fastcall TSendFiles::SetUpClick(TObject *Sender)
{
Notebook1->ActivePage="SetUp";
}
//---------------------------------------------------------------------------


//****************添加按钮事件*******************
void __fastcall TSendFiles::AddClick(TObject *Sender)
{
AnsiString FileName,TempName;                         //文件名
if (OpenDialog1->Execute())                           //打开文件对话框
  {
    for (int i=0;i<OpenDialog1->Files->Count;i++)
        {
         TempName=OpenDialog1->Files->Strings[i];     //取出全路经文件名
         FullFileName->Add(TempName);                 //保存
         FileName=ExtractFileName(TempName);          //取出无路经文件名
         ListView1->AddItem(FileName,NULL);           //在ListView中显示
        }
   Sent->Enabled=true;                                //发送按钮
   Cancel->Enabled=false;                             //取消按钮
  }
}
//---------------------------------------------------------------------------


void __fastcall TSendFiles::ListView1Resize(TObject *Sender)
{
ListView1->Columns->Items[0]->Width=ListView1->Width-5;
}
//---------------------------------------------------------------------------


//*****************清除**************************
void __fastcall TSendFiles::ClearClick(TObject *Sender)
{
FullFileName->Clear();
ListView1->Clear();
Sent->Enabled=false;
Cancel->Enabled=false;
Add->Enabled=true;
FSCMDS->Lines->Clear();
FRCMDS->Lines->Clear();
FSRepa->Lines->Clear();
FRError->Lines->Clear();
}
//---------------------------------------------------------------------------


//**************************发送数据到UDP控件************************
//**参数：CMD---命令码，Buffer---缓冲去指针，Size---数据长度
//*******************************************************************
void __fastcall TSendFiles::SendData_1(AnsiString CMD,char *Buffer,long Size)
{
SendData_1(CMD,Buffer,Size,0);                  //无Position方式发送数据
}

void __fastcall TSendFiles::SendData_1(AnsiString CMD,char *Buffer,long Size,long Position)
{
TSendFileData TempData;                             //临时数据缓冲
Application->ProcessMessages();
memset(&TempData,0,sizeof(TSendFileData));          //清除缓冲区

//**************************分析要发送的数据*********************************
TempData.Ver='1';
if (!(CMD=="FRLast"||CMD=="FSLast"))                //执行的不是"重发"命令
   {
   if (CMD=="FSCrea") TempData.Position=ReadFileSize;//建立文件命令借用Position传送文件长度
   if (CMD=="FSFile") TempData.Position=Position;   //传送文件时保存文件指针（当前Position已经读了Size字节)
   strcpy(TempData.FileFlage,CMD.c_str());          //保存命令码
   TempData.Size=Size;                              //保存数据长度
   memmove(&TempData.Data,Buffer,Size);             //把要发送的数据保存到临时数据中
   TempData.CRC=0;
   unsigned short CRC;
   CRC=CRC_16(&TempData.FileFlage[0],sizeof(TempData));//计算CRC校验码
   TempData.CRC=CRC;                                //保存CRC
   ErrorCount=0;                                    //错误计数器
   FSTimeOut=0;
   }
else                                                //执行"重发"命令
   {
   if (CMD=="FSLast")                               //发送方重发
       memmove(&TempData,&LastSendData,sizeof(TSendFileData));//把最后一次的发送方数据取出
   else
       memmove(&TempData,&LastReciveCMD,sizeof(LastReciveCMD));//把最后一次的接收方数据取出
   Size=TempData.Size;
   ErrorCount++;                                    //错误计数器+1
   if (ErrorCount>10)                               //重发超过10次
      {
        FSStatusBar->Panels->Items[1]->Text="传输错误,发送失败";
        return;
      }
   }
//***************准备发送******************************************************
   if (CMD.SubString(1,2)=="FS")                    //保存最后一次发送的数据
      {
       memmove(&LastSendData,&TempData,sizeof(TSendFileData));    //发送方数据
       FSTimer->Enabled=true;                              //启动超时定时计数器
      }
   else
      {
       memmove(&LastReciveCMD,&TempData,sizeof(LastReciveCMD));    //接受方响应数据
      }
   WriteToUDF(TempData.FileFlage,sizeof(TSendFileData)-1000+Size);  //发送数据包到UDP
}




//******************善后处理***********************
void __fastcall TSendFiles::FormDestroy(TObject *Sender)
{
delete ReadFile;
delete WriteFile;
delete [] WriteList;//删除文件块状态数据
ReadFile=NULL;
WriteFile=NULL;
}
//---------------------------------------------------------------------------


//***************发送UDP数据****************************
//此处为与主程序合并接口内容，奇怪的是如果用SendBuff发送，在2000下没问题，在9X下会出错
//所以这里用MyStream过渡了一下，改用SendStream发送。
//******************************************************
void __fastcall TSendFiles::WriteToUDF(char *Buffer,int Size)
{
NMUDP1->RemoteHost=RemoteIP->Text;
NMUDP1->RemotePort=RemotePort->Text.ToIntDef(6666);
TMemoryStream *MyStream =new TMemoryStream();
try
{
MyStream->WriteBuffer(Buffer,Size);
NMUDP1->SendStream(MyStream);
}
catch (...){}
delete MyStream;
}


//**************接收到的UDP数据******************************
//此处为与主程序的接口部分，判断FileFlag第一个字节为"F"，调Proc_Send_F。
//***********************************************************
void __fastcall TSendFiles::NMUDP1DataReceived(TComponent *Sender,
      int NumberBytes, AnsiString FromIP, int Port)
{
TSendFileData RecivedData;
memset(&RecivedData,0,sizeof(TSendFileData));

NMUDP1->RemoteHost=FromIP;
RemoteIP->Text=FromIP;
NMUDP1->RemotePort=Port;
RemotePort->Text=IntToStr(Port);

NMUDP1->ReadBuffer(&RecivedData.FileFlage[0],8192,NumberBytes);//接受数据
AnsiString Flag;
Flag=RecivedData.FileFlage;             //数据包类型
if (Flag.SubString(1,1)=="F")           //文件传送类数据
  {
   if (RecivedData.Ver=='1') Proce_Send_F_1(RecivedData);       //1版处理文件传送类数据包
  }
}
//---------------------------------------------------------------------------


//********************文件传送类数据处理程序******************
void __fastcall TSendFiles::Proce_Send_F_1(TSendFileData FileData)
{
Application->ProcessMessages();
unsigned short CRC1,CRC2;               //以下计算CRC校验码
CRC1=FileData.CRC;                      //传送来的CRC
FileData.CRC=0;
CRC2=CRC_16(&FileData.FileFlage[0],sizeof(TSendFileData));//计算CRC
AnsiString CMD,FileName;                //命令码，文件名
CMD=FileData.FileFlage;                 //取出对方送来的命令码
div_t x=div(FileData.Position,1000);    //计算包编号Index
int Index=x.quot;
if (x.rem>0) Index++;

if (CRC1!=CRC2)                         //校验错误，重发
   {
    if (CMD=="FSFile")                  //如果发来的是文件数据包
       {
        FRError->Lines->Add(IntToStr(Index));//显示CRC错误的包编号
        SendData_1("FRCRC","",0,FileData.Position);//通知发送方重发CRC错误的包
       }
    else                                //不是文件数据包，则要求发送方重发最后一个包
       {
        if (CMD.SubString(1,2)=="FR")   //收到的是接收方发来的命令(目前程序是作为发送方)
           SendData_1("FSRepa","",0);   //发送：发送方方发出的"重发"命令
        else                            //收到的是发送方发来的命令(目前程序是作为接收方)
           SendData_1("FRRepa","",0);   //发送：接收方发出的"重发"命令
       }
    return;
   }
//***********************以下是CRC校验正确的包*********************
if (CMD=="FSFile")                      //如果是文件数据包
   {
    WriteList[Index]=true;              //置对应包正确标志
   }
if (CMD.SubString(1,2)=="FR")           //收到的是接收端返回的信息
     {
      if (CMD!="FRRate") FRCMDS->Lines->Add(CMD);
      FSTimer->Enabled=false;           //关闭发送超时定时计数器
      if (FRCMD!="FRRead" &&FRCMD!="FREnd" && FRCMD==CMD) return;//正在执行发送端命令，忽略重复的命令
      if (CMD!="FRRate") FRCMD=CMD;                        //保存当前命令
     }
else                                    //收到的是发送端发来的信息
     {
     if (!(FSCMD=="FSFile"&&CMD=="FSFile")) FSCMDS->Lines->Add(CMD);
     if (CMD!="FSFile" &&CMD!="FSStop" && FSCMD==CMD) return;//正在执行接收端命令
     FSCMD=CMD;                          //保存当前命令
     }


//********************以下是接收方命令处理程序***************************************
if (CMD=="FSName")                      //发送来的数据是文件名
   {
    FSCMDS->Lines->Clear();
    FSCMDS->Lines->Add(CMD);
    FileName=FileData.Data;             //取出文件名
    if (ReciveType->ItemIndex==2)       //拒绝接收任何文件
       {
        SendData_1("FRReje","",0);      //向发送方发出拒绝接收文件指令
        return;
       }
    if (ReciveType->ItemIndex==1)       //向用户提示接收文件
       {
        if (MessageDlg("对方发来"+FileName+",接收吗？",mtConfirmation,mbOKCancel,0)!=mrOk)//用户拒绝
           {
            if (FRCMD!="FSCanc") SendData_1("FRReje","",0);//在此之前没有收到Cancel则向发送方发出拒绝接收文件指令
            return;
           }
       }
    if (FRCMD=="FSCanc") return;           //在此之前收到Cancel
    if (FileExists(GetDir()+"\\"+FileName))//检查指定路径下有无重名文件
         SendData_1("FRExis",FileName.c_str(),FileName.Length());//有，发送重名信息
    else SendData_1("FRNot",FileName.c_str(),FileName.Length()); //无，发送无重名信息
    return;
   }
if (CMD=="FSCrea")                      //发送来的数据是建立文件命令
   {
    if (WriteFile!=NULL)
       {
        return;
       }
    FileName=FileData.Data;             //取出文件名
    WriteFileSize=FileData.Position;    //取出并保存文件长度
    if (WriteListCount>0) delete [] WriteList;//删除文件块状态数据
    WriteListCount=0;                   //清文件块状态数
    div_t x;
    x=div(WriteFileSize,1000);          //计算文件块数量
    WriteListCount=x.quot;
    if (x.rem>0) WriteListCount++;
    WriteList=new bool [WriteListCount];//建立文件块状态数组
    for (int j=0;j<WriteListCount;j++) WriteList[j]=false;//置文件块状态
    try
    {
     WriteFile=new TFileStream(GetDir()+"\\"+FileName,fmCreate|fmShareDenyNone);//建立文件
     SendData_1("FRAll","",0);           //向发送方发出读文件指令
    }
    catch (...)
    {
     FRStatusBar->Panels->Items[1]->Text="建立"+FileName+"失败";
     SendData_1("FRErr","",0);              //向发送方发出写文件失败信息
    }
    TimerCount=0;                           //文件传送计时器
    Timer1->Enabled=true;
    FRBlocks=0;
    FRStatusBar->Panels->Items[2]->Text="00:00:00";
    FRError->Lines->Clear();
    FRError->Lines->Add("CRC错误的块");
    return;
   }
if (CMD=="FSFile")                        //发送方发来的是文件数据
   {
    if (WriteFile!=NULL)                  //有效的文件流
      {
       Cancel->Enabled=true;
       try
          {
           if (WriteFile->Size<=FileData.Position)      //当前块是文件尾(正常接收)
              FRStatusBar->Panels->Items[1]->Text=FormatFloat("###,###,###",FileData.Position+FileData.Size)+"/"+FormatFloat("###,###,###",WriteFileSize);
           else FRStatusBar->Panels->Items[1]->Text="纠错:"+IntToStr(FileData.Position);
           while (WriteFile!=NULL && WriteFile->Size<FileData.Position)    //如果当前块超过了文件尾
              {
               WriteFile->Seek(0,soFromEnd);            //写无用数据到文件
               WriteFile->WriteBuffer(FileData.Data,FileData.Size);
              }
           if (WriteFile==NULL) return ;
           WriteFile->Seek(FileData.Position,soFromBeginning);//写当前文件块
           WriteFile->WriteBuffer(FileData.Data,FileData.Size);
           FRBlocks++;
          }
       catch (...)
          {
           FRStatusBar->Panels->Items[1]->Text="写文件错误！";
           SendData_1("FRErr","",0);              //向发送方发出写文件错误信息
          }
      }
    return;
   }
if (CMD=="FSStop")                                //发送方发来的是文件发送结束指令
   {
    if (WriteFile!=NULL)                          //文件有效
      {
       int Poss[250];                             //需要重发的数据块
       int k=0;
       int j=0;
       FRError->Lines->Add("**需要重发的块**");
       while (j<WriteListCount-1)                 //搜索文件块数组
          {
           if (!WriteList[j])                     //错误的文件块
              {
              if (k<250)                          //一次最多发250个错误的文件块信息
                {
                 Poss[k]=j;                       //错误文件块编号数据
                 k++;                             //错误块计数器
                }
              FRError->Lines->Add(IntToStr(j*1000));
              }
           j++;
          }
       if (k>0)                                   //有错误的文件块
          {
           SendData_1("FRRead",(char *)Poss,k*sizeof(int));//向发送发错误块数据
          }
       else                                      //没有错误的数据块
          {
           delete WriteFile;                     //关闭文件
           WriteFile=NULL;
           FRBlocks=0;
           delete [] WriteList;                  //删除文件状态标志数组
           WriteListCount=0;                     //文件状态标志计数
           SendData_1("FREnd","",0);             //通知发送方文件传送完毕
           Timer1->Enabled=false;                //关闭文件传送计时器
           FRStatusBar->Panels->Items[1]->Text="接收完毕!";

          }
       }
    return;
   }
if (CMD=="FSCanc")                            //发送方发来的是中断命令
   {
    try
       {
        FileName=FileData.Data;               //取出文件文件名
        delete WriteFile;                     //关闭文件
        WriteFile=NULL;
        DeleteFile(GetDir()+"\\"+FileName);   //删除未接受完的文件
        SendData_1("FRCanc","",0);            //通知发送方已经中断
       }
    catch (...)
       {
       }
       FRStatusBar->Panels->Items[1]->Text="发送方中断传输";
    return;
   }

//************************执行重发命令*******************************

if (CMD=="FRRepa")                        //接收方发来的重发命令
   {
    SendData_1("FSLast","",0);            //执行发送方重发
    return;
   }
if (CMD=="FSRepa")                        //发送方发来的重发命令
   {
    SendData_1("FRLast","",0);            //执行接收方重发
    return;
   }

//************************以下是发送方命令处理程序********************
if (CMD=="FRRate")
   {
    memmove(&Rate,FileData.Data,sizeof(float));
    return;
   }
if (CMD=="FRCRC")                         //接收方发来的是CRC校验错信息
   {
    SendFile_1(FileData.Position);        //重发错误的文件块
    FSRepa->Lines->Add(IntToStr(FileData.Position));
    return;
   }
if (CMD=="FRCanc") return;              //接收方已经中断
if (CMD=="FRReje")                      //接收方发来拒绝接收指令
   {
    if (FSTimeOut>MaxTimeOut->Text.ToIntDef(60)) return;      //超时
    if (MessageDlg("对方拒绝接收,重试吗？",mtConfirmation,mbOKCancel,0)==mrOk)
       {
        SendData_1("FSLast","",0);        //重试
        return;
       }
    else CMD="FREnd";                   //结束发送
   }
if (CMD=="FRNot")                       //接收方发来文件无重名消息
   {
    if (FSTimeOut>MaxTimeOut->Text.ToIntDef(60)) return;      //超时
    StartSend();                        //开始发送文件
    return;
   }
if (CMD=="FRExis")                      //接收方发来文件重名消息
   {
    if (!Cancel->Enabled) return;       //已经Cancel
    if (FSTimeOut>MaxTimeOut->Text.ToIntDef(60)) return;      //超时
    FileName=FileData.Data;             //取出文件名，弹出对话框
    if (MessageDlg(FileName+"\r\n同名的文件已经存在，覆盖吗？",mtConfirmation,mbOKCancel,0)==mrOk)
      {
       StartSend();                     //开始发送文件
       return;
      }
    else CMD="FREnd";                   //用户选择"No"，执行结束文件发送命令
   }
if (CMD=="FRAll")                       //接收方发来的是传送文件命令
   {
    if (ReadFile!=NULL)                 //文件有效
       {
        if (ReadFile->Position>0) return;//文件已经开始传送
        TimerCount=0;                   //文件传送计时器
        FSBlocks=0;
        Timer1->Enabled=true;
        FSStatusBar->Panels->Items[2]->Text="00:00:00";
        int Pos=0;
        while (Pos<ReadFileSize&&ReadFile!=NULL)//循环发送文件块
           {
            try
              {
               if (!Cancel->Enabled) return;//用户按下了"取消"健
               Pos+=SendFile_1(Pos);    //发送文件块
               if (Cancel->Enabled) FSStatusBar->Panels->Items[1]->Text=FormatFloat("###,###,###",Pos)+"/"+FormatFloat("###,###,###",ReadFileSize);
               else FSTimer->Enabled=false;
              }
            catch (...)
              {
              FSStatusBar->Panels->Items[1]->Text="读文件错误!";
              }
           }
        SendData_1("FSStop","",0);      //通知接收方传送完毕
       }
    else
       {
        FSStatusBar->Panels->Items[1]->Text="文件未打开!";
       }
    return;
   }
if (CMD=="FRRead")                      //发送方按接收方发来的块号传送文件块(用于纠错)
   {
    if (ReadFile!=NULL)
       {
        int Pos[250];                   //文件块号数组
        memmove(Pos,FileData.Data,FileData.Size);//取出接收方发来块号数据
        int n=FileData.Size/sizeof(int);//要发的块数量
        for (int j=0;j<n;j++)
           {
            try
              {
               if (!Cancel->Enabled) return;//用户按下了"取消"健
               SendFile_1(Pos[j]*1000); //发送所需要的文件块
               FSRepa->Lines->Add(IntToStr(Pos[j]*1000));
               if (Cancel->Enabled) FSStatusBar->Panels->Items[1]->Text="重发:"+FormatFloat("###,###,###",Pos[j]*1000);
               else FSTimer->Enabled=false;
              }
            catch (...)
              {
              FSStatusBar->Panels->Items[1]->Text="读文件错误!";
              }
           }
        SendData_1("FSStop","",0);      //通知接收方传输完毕
       }
    else
       {
        FSStatusBar->Panels->Items[1]->Text="文件未打开!";
       }
    return;
   }
if (CMD=="FRErr")                      //接收方发来写错误消息
   {
    if (MessageDlg("接收方写文件失败！重试吗？",mtConfirmation,mbOKCancel,0)==mrOk)
      {
       SendData_1("FSLast","",0);      //重发
       return;
      }
    else CMD="FREnd";                  //用户选择"No"，执行结束文件发送命令
   }
if (CMD=="FREnd")                      //接收方发来文件传输结束信息
   {
   if (ReadFile==NULL)
      {
       FSStatusBar->Panels->Items[1]->Text="停止发送!";
       Sent->Enabled=false;                      //界面处理
       Cancel->Enabled=false;
       Add->Enabled=true;
       Clear->Enabled=true;
       SetUp->Enabled=true;
       return;
      }
   delete ReadFile;                    //关闭文件
   ReadFile=NULL;
   Timer1->Enabled=false;              //关闭文件传输计时器
   ListView1->Items->Delete(0);        //删掉已经发送的文件信息
   FullFileName->Delete(0);
   if (ListView1->Items->Count>0)      //还有未发送的文件
      {
       FSRepa->Lines->Clear();
       FRCMDS->Lines->Clear();
       FileName=ExtractFileName(FullFileName->Strings[0]);      //取出文件名
       SendData_1("FSName",FileName.c_str(),FileName.Length());   //发送文件名信息
       ListView1->ItemIndex=0;
      }
   else                                          //文件已经全部发送完毕
      {
       Sent->Enabled=false;                      //界面处理
       Cancel->Enabled=false;
       Add->Enabled=true;
       Clear->Enabled=true;
       SetUp->Enabled=true;
      }
    FSStatusBar->Panels->Items[1]->Text="发送完毕!";
    return;
   }
}
void __fastcall TSendFiles::FormCreate(TObject *Sender)
{
Dir->Text=GetCurrentDir();                       //初始路径(移植时要增加保存上次值的功能)
}
//---------------------------------------------------------------------------

void __fastcall TSendFiles::SentClick(TObject *Sender)  //发送按钮
{
AnsiString FileName;
FileName=ExtractFileName(FullFileName->Strings[0]);     //文件名
SendData_1("FSName",FileName.c_str(),FileName.Length());  //发送文件名信息
FSStatusBar->Panels->Items[1]->Text="";
FSStatusBar->Panels->Items[2]->Text="";
FSStatusBar->Panels->Items[3]->Text="";
ListView1->ItemIndex=0;
Sent->Enabled=false;
Add->Enabled=false;
Cancel->Enabled=true;
Clear->Enabled=false;
SetUp->Enabled=false;
FSRepa->Lines->Clear();
FSRepa->Lines->Add("CRC错误重发块");
FSCMDS->Lines->Clear();

}
//---------------------------------------------------------------------------


void __fastcall TSendFiles::StartSend()                 //开始发送文件
{
 FRCMDS->Lines->Clear();
 FRCMDS->Lines->Add(FRCMD); 
 if (FSTimeOut>MaxTimeOut->Text.ToIntDef(60)) return;      //超时
 AnsiString FileName=FullFileName->Strings[0];          //文件名
 try
    {
    delete ReadFile;
    ReadFile=NULL;
    ReadFile=new TFileStream(FileName,fmOpenRead|fmShareDenyNone);//打开文件
    }
 catch (...)
    {
    FSStatusBar->Panels->Items[1]->Text="打开文件失败！";
    }
 ReadFileSize=ReadFile->Size;                        //未读字节数
 AnsiString WriteName=ExtractFileName(FileName);     //文件名
 SendData_1("FSCrea",WriteName.c_str(),WriteName.Length());//发送建立文件命令
}

void __fastcall TSendFiles::FSTimerTimer(TObject *Sender) //发送方超时定时器计数器
{
FSTimeOut++;                                               //计数器
AnsiString CMD=LastSendData.FileFlage;                     //最后一次发送的命令
CMD=CMD.SubString(1,6);                                    //取出命令码
if (CMD!="FSName" && CMD!="FSFile")                        //如果发送的是文件名和文件块数据命令，不执行重发
  {
   int temp=FSTimeOut/3;                                   //3秒钟重发一次
   if (temp*3==FSTimeOut)
      {
       SendData_1("FSLast","",0);                          //重发
      }
  }
if (FSTimeOut<5) return;        //小于5秒不显示信息
if (FSTimeOut<20) FSStatusBar->Panels->Items[1]->Text=FSStatusBar->Panels->Items[1]->Text+".";
else FSStatusBar->Panels->Items[1]->Text="............."+IntToStr(FSTimeOut)+"秒";
if (FSTimeOut>MaxTimeOut->Text.ToIntDef(60))               //超时
   {
    FSTimer->Enabled=false;                               //关闭定时器
    if (CMD!="FSName") FSStatusBar->Panels->Items[1]->Text="发送失败,网络超时。";
    else FSStatusBar->Panels->Items[1]->Text="发送失败,对方无应答。";
    delete ReadFile;
    ReadFile=NULL;
    FSTimeOut=0;
    if (ListView1->Items->Count>0)
     {
      Sent->Enabled=true;                                //界面按钮设置
      Add->Enabled=false;
     }
    else
     {
      Sent->Enabled=false;
      Add->Enabled=true;
     }
    Clear->Enabled=true;
    SetUp->Enabled=true;
    Cancel->Enabled=false;
   }
}
//---------------------------------------------------------------------------



void __fastcall TSendFiles::CancelClick(TObject *Sender)     //发送过程中的"取消"
{
if (ReadFile!=NULL)
   {
    if (MessageDlg("正在发送文件...,停止吗！",mtConfirmation,TMsgDlgButtons() << mbYes<<mbNo,0)==mrNo) return;
    if (ListView1->Items->Count>0)                          //界面按钮设置
         {
          Sent->Enabled=true;
          Add->Enabled=false;
         }
    else
         {
          Sent->Enabled=false;
          Add->Enabled=true;
         }
    Clear->Enabled=true;
    SetUp->Enabled=true;
    Cancel->Enabled=false;
    AnsiString FileName=ExtractFileName(FullFileName->Strings[0]); //取出正在发送的文件名
    SendData_1("FSCanc",FileName.c_str(),FileName.Length());         //通知接收方中断发送
    try
       {
        delete ReadFile;                                             //关闭正在发送的文件
        ReadFile=NULL;
       }
    catch(...){}
    FSStatusBar->Panels->Items[1]->Text="用户中断";
    FSTimer->Enabled=false;
    FSTimeOut=0;
   }
if (WriteFile!=NULL)
   {
    if (MessageDlg("正在接收文件...,停止吗！",mtConfirmation,TMsgDlgButtons() << mbYes<<mbNo,0)==mrNo) return;
    delete WriteFile;
    WriteFile=NULL;
    Cancel->Enabled=false;
    SendData_1("FREnd","",0);
    SendData_1("FREnd","",0);
    SendData_1("FREnd","",0);
    SendData_1("FREnd","",0);
    FRStatusBar->Panels->Items[1]->Text="中断接收";
   }
}
//---------------------------------------------------------------------------


AnsiString __fastcall TSendFiles::GetDir()      //取保存文件的路径
{
 AnsiString Direct=Dir->Text;
 while (Direct.SubString(Direct.Length(),1)=="\\") Direct.Delete(Direct.Length(),1);
 return Direct;
}
//---------------------------------------------------------------------------


//**********生成CRC校验码表****************************
void __fastcall TSendFiles::BuildTable16(unsigned short aPoly)
{
    unsigned short i, j;
    unsigned short nData;
    unsigned short nAccum;

    for ( i = 0; i < 256; i++ )
    {
        nData = ( unsigned short )( i << 8 );
        nAccum = 0;
        for ( j = 0; j < 8; j++ )
        {
            if ( ( nData ^ nAccum ) & 0x8000 )
                nAccum = ( nAccum << 1 ) ^ aPoly;
            else
                nAccum <<= 1;
            nData <<= 1;
        }
        Table_CRC[i] = ( unsigned long )nAccum;
    }
}
//---------------------------------------------------------------------------


//**********计算CRC校验码****************************
unsigned short __fastcall TSendFiles::CRC_16( unsigned char * aData, unsigned long aSize )
{
    unsigned long  i;
    unsigned short nAccum = 0;

    for ( i = 0; i < aSize; i++ )
        nAccum = ( nAccum << 8 ) ^ ( unsigned short )Table_CRC[( nAccum >> 8 ) ^ *aData++];
    return nAccum;
}
//---------------------------------------------------------------------------


int __fastcall TSendFiles::SendFile_1(int Position)
{
 char Buffer[1024];
 int Size;
try
 {
 if (ReadFile==NULL) return 0;
 if (ReadFile->Size-Position>1000) Size=1000;
 else Size=ReadFile->Size-Position;
 ReadFile->Seek(Position,soFromBeginning);
 ReadFile->ReadBuffer(Buffer,Size);
 SendData_1("FSFile",Buffer,Size,Position);
 FSBlocks++;
 Delay(SleepTime);
 return Size;
 }
catch (...)
 {
 FSStatusBar->Panels->Items[1]->Text="读文件错误!";
 return -1;
 }
}
//---------------------------------------------------------------------------


void __fastcall TSendFiles::Timer1Timer(TObject *Sender)//文件传输计时器
{
float FSRate=FSBlocks*1000/1024.0;
float FRRate=FRBlocks*1000/1024.0;
FSBlocks=0;
FRBlocks=0;
TimerCount++;
int hh,mm,ss;
ss=TimerCount;
hh=ss/3600;
ss=ss-hh*3600;
mm=ss/60;
ss=ss-mm*60;
if (FRRate>0)
   {
    LastFRRate=(LastFRRate+FRRate)/2;
    FRStatusBar->Panels->Items[3]->Text=FormatFloat("0.0",LastFRRate)+"k/s";
    FRStatusBar->Panels->Items[2]->Text= FormatDateTime("hh:mm:ss",EncodeTime(hh,mm,ss,0));
    SendData_1("FRRate",(char *) &LastFRRate,sizeof(float));
   }
if (FSRate>0)
   {
    LastFSRate=(LastFSRate+FSRate)/2;
    if (Speed->Down)
       {
        float Rate0=(LastFSRate-Rate)/LastFSRate;
        if (Rate0<0) Rate0=-1*Rate0;
        if (Rate0>0 && Rate0>0.15) SleepTime+=1;
        if (Rate0>0 && SleepTime>1 && Rate0<0.05) SleepTime-=1;
       }
    else
       {
        if (LastFSRate>23) SleepTime+=10;
        if (LastFSRate<18) SleepTime-=10;
       }
    FSStatusBar->Panels->Items[3]->Text=FormatFloat("0.0",LastFSRate)+"k/s,"+IntToStr(SleepTime);
    FSStatusBar->Panels->Items[2]->Text= FormatDateTime("hh:mm:ss",EncodeTime(hh,mm,ss,0));
   }
}
//---------------------------------------------------------------------------

void __fastcall TSendFiles::FormCloseQuery(TObject *Sender, bool &CanClose)
{
if (ReadFile!=NULL)
   {
    if (MessageDlg("正在发送文件...,停止吗！",mtConfirmation,TMsgDlgButtons() << mbYes<<mbNo,0)==mrYes)
       {
        delete ReadFile;
        ReadFile=NULL;
        CanClose=true;
       }
    else CanClose=false;
   }
if (WriteFile!=NULL)
   {
    if (MessageDlg("正在接收文件...,停止吗！",mtConfirmation,TMsgDlgButtons() << mbYes<<mbNo,0)==mrYes)
       {
        delete WriteFile;
        WriteFile=NULL;
        CanClose=true;
       }
    else CanClose=false;
   }
}
//---------------------------------------------------------------------------

void __fastcall TSendFiles::SpeedClick(TObject *Sender)
{
if (Speed->Down)
   {
    Speed->Caption="自动";
    Speed->Hint="自动调整到最佳速度";
   }
else
   {
    Speed->Caption="限速";
    Speed->Hint="限制传输速度以保证语音传送";
   }
}
//---------------------------------------------------------------------------



void __fastcall TSendFiles::Delay(int n)
{
long t1,t2;
t1=t2=timeGetTime();
while (abs(t2-t1)<n)
   {
    Application->ProcessMessages();
    t2=timeGetTime();
   }
}
