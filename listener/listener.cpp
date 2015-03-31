#include "listener.h"

#include "geckoembed_config.h"

#include <iostream>
#include <string>
#include <iomanip>

SampleListener::SampleListener(MozView *aMozView)
{
    mMozView=aMozView;
}

void SampleListener::StatusChanged(const char* newStatus, PRUint32 statusType)
{
	std::cout << "Status changed to " << string(newStatus) << std::endl;
}

void SampleListener::DocumentLoaded(bool aSuccess)
{
	if(aSuccess ) {
		std::cout << "Document Loaded successful" << std::endl;
	} else {
		std::cout << "Document loaded unsuccessful" << std::endl;
	}
}

