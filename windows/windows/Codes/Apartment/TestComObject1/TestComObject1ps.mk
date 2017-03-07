
TestComObject1ps.dll: dlldata.obj TestComObject1_p.obj TestComObject1_i.obj
	link /dll /out:TestComObject1ps.dll /def:TestComObject1ps.def /entry:DllMain dlldata.obj TestComObject1_p.obj TestComObject1_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del TestComObject1ps.dll
	@del TestComObject1ps.lib
	@del TestComObject1ps.exp
	@del dlldata.obj
	@del TestComObject1_p.obj
	@del TestComObject1_i.obj
