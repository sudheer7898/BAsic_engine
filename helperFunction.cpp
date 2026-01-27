#include "helperFunction.hpp"

void setAddress(std::shared_ptr<GameObject>& objPtr, GameObject* rawPtr)
{
	objPtr->m_parent = std::shared_ptr<GameObject>(rawPtr);
}
