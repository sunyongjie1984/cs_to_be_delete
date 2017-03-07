//------------------------------------------------------------------------------
// AUTHOR  : OAM generic Team
// PROJECT : OAM generic
// DOMAIN  : 
//------------------------------------------------------------------------------
//           Versions and editions historic
//------------------------------------------------------------------------------
//    Ver    | Ed |   date     | resp.                 | comment
//-----------+----+------------+-----------------------+------------------------
//           | 01 | 08/10/2010 | Deng Qiongbo          | creation - ref FwkConfigurator.hh in DDM code
//-----------+----+------------+-----------------------+------------------------

#ifndef GOAM_CONFIGURATOR_H
#define GOAM_CONFIGURATOR_H

#include "System/Configurator/FwkConfigurator.hh"

const string GOAM_PF_GENERIC_FILE = "goam_pf_generic.cfg";
const string GOAM_CONF_DIR = "/usr/oam_gen/data";


namespace goam
{
    /**
    * \class GoamConfigurator  
    * \brief load and store GOAM configuration items
    * 
    * OAM configruation item defined in OAM configuration file will override the same one defined in GOAM configuration file 
    */
    class GoamConfigurator
    {
    public:
        GoamConfigurator(string processName_, string configPath_ = ""): _confImpl(NULL) 
        {
            load(processName_, configPath_);
        }
        
        ~GoamConfigurator();
        
        static GoamConfigurator* getInstance() 
        {
            if(_instance == NULL) 
            {
                _instance = new GoamConfigurator;
            }
            
            return _instance;
        }
        
        static int init(string processName_ = "", string configPath_ = "") 
        { 
            return getInstance()->load(processName_, configPath_); 
        }
        
        DhaFw::FwkConfigurator *getImplem() const { return _confImpl;}

    protected:
        int load(const string & processName_, const string & configPath_);
        
    private:
        GoamConfigurator():_confImpl(NULL){}
        
    private:
        static GoamConfigurator* _instance;
        
        DhaFw::FwkConfigurator * _confImpl;
                   
    
    }; // class GoamConfigurator

    class GoamSConfigurator
    {
    public:
        enum error { SUCCEED = 0, UNKNOWN_SYMBOL = -2, CONVERT_ERROR = -1 };
        
        static TrSv::Long getShort(string symbol_, TrSv::Short &val_)
        { 
            return GoamConfigurator::getInstance()->getImplem()->getVariable(symbol_, val_); 
        }

        static TrSv::Long getUShort(string symbol_, TrSv::UShort &val_)
        { 
            return GoamConfigurator::getInstance()->getImplem()->getVariable(symbol_, val_); 
        }

        static TrSv::Long getLong(string symbol_, TrSv::Long &val_)
        { 
            return GoamConfigurator::getInstance()->getImplem()->getVariable(symbol_, val_); 
        }

        static TrSv::Long getULong(string symbol_, TrSv::ULong &val_)
        { 
            return GoamConfigurator::getInstance()->getImplem()->getVariable(symbol_, val_); 
        }
        
        static TrSv::Long getLongLong(string symbol_, TrSv::LongLong &val_)
        { 
            return GoamConfigurator::getInstance()->getImplem()->getVariable(symbol_, val_); 
        }
        
        static TrSv::Long getULongLong (string symbol_, TrSv::ULongLong &val_)
        { 
            return GoamConfigurator::getInstance()->getImplem()->getVariable(symbol_, val_); 
        }
        
        static TrSv::Long getString(string symbol_, string &val_)
        { 
            return GoamConfigurator::getInstance()->getImplem()->getVariable(symbol_, val_); 
        }
    }; //class GoamSConfigurator

} //namespace goam

#endif //GOAM_CONFIGURATOR_H
