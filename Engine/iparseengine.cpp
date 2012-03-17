#include "iparseengine.h"


//=============================================================================
IParseEngine::IParseEngine()
{
}

//=============================================================================

ServerType IParseEngine::getServerType()
{
    return mServerType;
}

//=============================================================================
bool IParseEngine::setServerType(ServerType aServerType)
{
    mServerType = aServerType;
    return true;
}

//=============================================================================
//endif
