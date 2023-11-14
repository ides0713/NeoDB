#include "common/common_def.h"

NeoBaseObject::NeoBaseObject()
{
	type_ = TypeTag::UNDEFINED;
}

NeoBaseObject::NeoBaseObject(TypeTag type)
{
	type_ = type;
}
