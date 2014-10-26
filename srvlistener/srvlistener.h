#ifndef SRVLISTENER_H
#define SRVLISTENER_H

#include "nsCOMPtr.h"
#include "embed.h"
using namespace std;
class SrvListener : public MozViewListener
{
public:
    SrvListener(MozView *aMozView);

    void StatusChanged(const char* newStatus, PRUint32 statusType);
    void DocumentLoaded(bool /*aSuccess*/);
private:
    MozView *mMozView;
};

#endif // SRVLISTENER_H

