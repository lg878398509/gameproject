#include "TowerPos.h"

TowerPos::TowerPos() {
    m_pos = Point(0, 0);
    m_isDebug = false;
}

TowerPos::~TowerPos() {
}

TowerPos* TowerPos::create( Point pos ) {
    TowerPos* tPos = new TowerPos();

    if(tPos && tPos->init(pos)) {
        tPos->autorelease();
    }
    else {
        CC_SAFE_DELETE(tPos);
    }

    return tPos;
}

TowerPos* TowerPos::create( Point pos, bool isDebug ) {
    TowerPos* tPos = new TowerPos();

    if(tPos && tPos->init(pos, isDebug)) {
        tPos->autorelease();
    }
    else {
        CC_SAFE_DELETE(tPos);
    }

    return tPos;
}
bool TowerPos::init( Point pos ) {
    bool bRet = false;

    do {
        CC_BREAK_IF(! PosBase::init(pos));
        bRet = true;
    } while (0);

    return bRet;
}

bool TowerPos::init( Point pos, bool isDebug ) {
    bool bRet = false;

    do {
        CC_BREAK_IF(! PosBase::init(pos, isDebug));

        bRet = true;
    } while (0);

    return bRet;
}

void TowerPos::draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t flags) {
	if (m_isDebug) {
		_customCommand.init(_globalZOrder);
		_customCommand.func = CC_CALLBACK_0(TowerPos::onDraw, this, transform, flags);
		renderer->addCommand(&_customCommand);
	}
}

void TowerPos::onDraw(const cocos2d::Mat4& transform, uint32_t flags) {

	/* 方式一 */
	Director* director = Director::getInstance();
	director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
	director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, transform);

	glLineWidth(5.0f);	// 设置画笔粗细

						/* 绘制矩形 */
	Vec2 srcPos = Vec2(m_pos.x - RADIUS, m_pos.y + RADIUS);
	Vec2 destPos = Vec2(m_pos.x + RADIUS, m_pos.y - RADIUS);
	//DrawPrimitives::drawRect(srcPos, destPos);

	auto draw = DrawNode::create();
	draw->drawRect(srcPos, destPos, Color4F(1, 1, 0, 1));

	glLineWidth(1);	// 恢复画笔粗细
					//添加到场景中，不然不会显示
	this->addChild(draw, 10);
	director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);;// 结束绘制


																	///* 方式二 */
																	//CHECK_GL_ERROR_DEBUG();
																	//DrawPrimitives::setDrawColor4F(1, 1, 0, 1);
																	//Vec2 src = Vec2(400 - RADIUS, 400 + RADIUS);
																	//Vec2 dest = Vec2(400 + RADIUS, 400 - RADIUS);
																	//DrawPrimitives::drawRect(src, dest);

}

bool TowerPos::isClickMe( Point pos ) {
    Point srcPos = Point(m_pos.x - RADIUS, m_pos.y + RADIUS);
    Point destPos = Point(m_pos.x + RADIUS, m_pos.y - RADIUS);

    if(pos.x >= srcPos.x && pos.x <= destPos.x && pos.y <= srcPos.y && pos.y >= destPos.y) {
        return true;
    }

    return false;
}

