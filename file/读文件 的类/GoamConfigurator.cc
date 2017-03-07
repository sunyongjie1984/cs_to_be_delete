//------------------------------------------------------------------------------
// AUTHOR  : OAM generic Team
// PROJECT : OAM generic
// DOMAIN  : 
//------------------------------------------------------------------------------
//           Versions and editions historic
//------------------------------------------------------------------------------
//    Ver    | Ed |   date     | resp.                 | comment
//-----------+----+------------+-----------------------+------------------------
//           | 01 | 08/10/2010 | Deng Qiongbo          | creation
//-----------+----+------------+-----------------------+------------------------
#include <stdarg.h>
#include <fstream>
#include <sys/stat.h>

#include "GoamConfigurator.hh"

using namespace std;

namespace goam
{
GoamConfigurator * GoamConfigurator::_instance  = NULL;

GoamConfigurator::~GoamConfigurator() 
{
    if(_confImpl != NULL) 
        delete _confImpl;        
}      
      
int GoamConfigurator::load(const string & processName_, const string & configPath_) 
{
    if(_confImpl == NULL) _confImpl = new DhaFw::TrSvConfigurator(""); //load DDM configuration, it may cost unnecessary time


    //read goam configuration file in GOAM_CONF_DIR
    _confImpl->TrSvParseFile(processName_, string(GOAM_CONF_DIR) + "/" + GOAM_PF_GENERIC_FILE);    

    struct stat desc;        
    //read oam configuration files in configPath_
    if(!configPath_.empty() && configPath_ != GOAM_CONF_DIR) 
    {
        if (!stat(configPath_.c_str(), &desc) != -1) 
        {
            if(S_ISDIR( desc.st_mode)) 
            {
                //read standard framework files in configPath_
                _confImpl->TrSvParseFile(processName_, configPath_ + "/" + DHFW_PF_GENERIC_FILE);
        
                //read processName_ prefixed files in configPath_
                if(!processName_.empty()) 
                {
                    _confImpl->TrSvParseFile(processName_, configPath_ + "/" + processName_ + DHFW_PF_GENERIC_FILE);
                }
            } 
            else if(S_ISREG( desc.st_mode)) 
            {
                _confImpl->TrSvParseFile(processName_, configPath_);
            }
        } 
        else 
        {
            Hlr_trace_err("could not open %s", configPath_.c_str());
            return -1;
        } 
    }
    return 0;
}

} //namespace goam
