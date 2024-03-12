#pragma once

// typedef short TypeTag;

enum class TypeTag
{
	UNDEFINED = 0,
};

// 需要在系统中不同模块进行转存的类需要继承自NeoBaseObject
// 目前该类仅含有标识类型的头部
class NeoBaseObject
{
public:
	NeoBaseObject();
	NeoBaseObject(TypeTag type);

private:
	TypeTag type_;
};