#pragma once

// typedef short TypeTag;

enum class TypeTag
{
	UNDEFINED = 0,
};

class NeoBaseObject
{
public:
	NeoBaseObject(TypeTag type = TypeTag::UNDEFINED);

private:
	TypeTag type_;
};