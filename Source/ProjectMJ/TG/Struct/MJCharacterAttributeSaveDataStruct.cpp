#include "MJCharacterAttributeSaveDataStruct.h"

FCharacterAttributeSaveData& FCharacterAttributeSaveData::operator=(const UMJCharacterAttributeSet& AttributeSet)
{

	// TODO 꼭 저장해야 하는 플레이어 정보들만 저장하기
	

	return *this;
}

void FCharacterAttributeSaveData::ApplyToAttributeSet(UMJCharacterAttributeSet& AttributeSet) const
{
	// TODO 저장한 정보 복구
}

