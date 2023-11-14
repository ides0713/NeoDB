#include "common/toolkit.h"

// 这是用于进行类型比较的函数, 这一函数的比较对象都是基于NeoBaseObject派生出来的, 换言之,
// 一般的数据类型, 如 int float 等进行比较不能通过
// TODO: 目前没有必须使用equal进行比较的情况
bool common::equal(void *obj1, void *obj2)
{
	return false;
}