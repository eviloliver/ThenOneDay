// ThenOneDayStudio

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Blueprint/UserWidget.h"
#include "MJSkillSlotWidget.generated.h"

enum class ESkillType : uint8;
class UButton;
/**
 * 
 */
class UTextBlock;
class UImage;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnClickedEquipButton,UTexture2D*,icon,ESkillType,type,FGameplayTag,SkillTag);
UCLASS()
class PROJECTMJ_API UMJSkillSlotWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> SkillImage;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> SkillName;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> SkillDescription;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> SkillType;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> SkillLevel;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> HideImage;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Equip;

	UPROPERTY()
	UTexture2D* SkillIcon;

	UPROPERTY()
	ESkillType Type;

	FGameplayTag SkillTag;
public:
	UFUNCTION()
	virtual void NativeConstruct() override;

	UFUNCTION()
	void SetSkillWidget(FGameplayTag Tag, UTexture2D* Image, FText Name, FText Description, ESkillType ype, int32 Level);
	void SetEquipedSkillTag(FGameplayTag Tag);
	void SetSkillImage(UTexture2D* Image);
	void SetSkillName(FText Name);
	void SetSkillDescription(FText Description);
	void SetSkillType(ESkillType type);
	void SetSkillLevel(int32 Level);

	UFUNCTION()
	void OnClicked_EquipButton();

	UButton* GetEquipButton() {return Equip;}
	UTexture2D* GetSkillIcon() {return SkillIcon;}
	ESkillType GetSkillType() {return Type;}

	FOnClickedEquipButton OnClickedEquipButton;
	
};