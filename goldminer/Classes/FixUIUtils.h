#ifndef FixUIUtils_h  
#define FixUIUtils_h  
#include "cocos2d.h"  

using namespace cocos2d;
using namespace std;

class FixUIUtils
{
public:
	FixUIUtils();

	~FixUIUtils();

	static void init();

	static void setFixScale(Node *node);

	static void setScaleMin(Node* node);

	static void setScaleMax(Node* node);

	static void setRootNodewithFIXED(Node* node);

	static void fixScene(Node* node);

	static void fixUI(Node* node);

};
#endif /* FixUIUtils_h */  
