#ifndef _Live_Live_h
#define _Live_Live_h

#include <CtrlLib/CtrlLib.h>

using namespace Upp;

#define LAYOUTFILE <Live/Live.lay>
#include <CtrlCore/lay.h>

class Live : public WithLiveLayout<TopWindow> {
public:
	Live();
};

#endif
