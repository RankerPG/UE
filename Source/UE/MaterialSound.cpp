#include "MaterialSound.h"

UMaterialSound::UMaterialSound()
{

}

bool UMaterialSound::Load_Sound(const FString& strName, const FString& strPath)
{
	USoundBase* pSound = LoadObject<USoundBase>(nullptr, *strPath);

	if (!IsValid(pSound))
		return false;

	m_SoundMap.Add(strName, pSound);

	return true;
}

USoundBase* UMaterialSound::Find_Sound(const FString& strName)
{
	USoundBase* const* ppSound = m_SoundMap.Find(strName);

	if (!ppSound)
		return nullptr;

	return *ppSound;
}