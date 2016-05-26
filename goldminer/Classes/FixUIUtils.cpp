//  
//  FixUIUtils.cpp  
//  MapTest  
//  
//  Created by Alostz on 16/4/16.  
//  
//  

#include <FixUIUtils.h>  
static cocos2d::Size designSize = cocos2d::Size(960, 640);
static cocos2d::Size screenSize;
static float minScale;
static float maxScale;

static float xScale;

static float yScale;

FixUIUtils::FixUIUtils() {

}

FixUIUtils::~FixUIUtils() {

}

void FixUIUtils::init() {
	screenSize = Director::getInstance()->getVisibleSize();
	xScale = designSize.width / screenSize.width;
	yScale = designSize.height / screenSize.height;
	minScale = MIN(screenSize.height / designSize.height, screenSize.width / designSize.width);
	maxScale = MAX(screenSize.height / designSize.height, screenSize.width / designSize.width);

	log("xScale = %f * xyScale = %f \n screenSize.width = %f * screenSize.height = %f \n", xScale, yScale, screenSize.width, screenSize.height);

}

//1��������layout�㵽��Ļ��С  
void FixUIUtils::setFixScale(Node *node) {
	auto nodeX = node->getScaleX();
	auto nodeY = node->getScaleY();
	log("setFixScale nodeX = %f * nodeX = %f \n", nodeX, nodeY);
	nodeX = nodeX * xScale;
	nodeY = nodeY * yScale;

	log("setFixScale nodeX = %f * nodeX = %f \n", nodeX, nodeY);
	node->setScaleX(nodeX);
	node->setScaleY(nodeY);
}

//��Ļ���߷ֱ����Ʒֱ��ʿ��߼����������ӣ�ȡ��(��)����Ϊ���ߵ��������ӡ�  
//�����ڿؼ�������  
void FixUIUtils::setScaleMax(Node *node) {
	auto nodeX = node->getScaleX();
	auto nodeY = node->getScaleY();
	log("setScaleMax nodeX = %f * nodeX = %f \n", nodeX, nodeY);

	nodeX = nodeX * maxScale;
	nodeY = nodeY * maxScale;
	log("setScaleMax nodeX = %f * nodeX = %f \n", nodeX, nodeY);

	node->setScaleX(nodeX);
	node->setScaleY(nodeY);
}

//��Ļ���߷ֱ����Ʒֱ��ʿ��߼����������ӣ�ȡ��(С)����Ϊ���ߵ��������ӡ�  
//�����ڱ���������  
void FixUIUtils::setScaleMin(Node *node) {
	auto nodeX = node->getScaleX();
	auto nodeY = node->getScaleY();
	log("setScaleMin nodeX = %f * nodeX = %f \n", nodeX, nodeY);

	nodeX = nodeX * minScale;
	nodeY = nodeY * minScale;
	log("setScaleMin nodeX = %f * nodeX = %f \n", nodeX, nodeY);

	node->setScaleX(nodeX);
	node->setScaleY(nodeY);
}


void FixUIUtils::setRootNodewithFIXED(Node* node) {
	auto moveX = (designSize.width - screenSize.width);
	auto moveY = (designSize.height - screenSize.height);
	node->setPosition(Point(-moveX, -moveY));
}

void FixUIUtils::fixScene(Node* node) {
	fixUI(node);
	FixUIUtils::setRootNodewithFIXED(node);
}


void FixUIUtils::fixUI(Node* node) {
	Vector<Node*> ChildrenList = node->getChildren();

	for (Node* child : ChildrenList) {
		log("fixUI nodeX = %d \n", child->getTag());
		FixUIUtils::setScaleMin(child);
	}

}