// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ClearBBValue.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_ClearBBValue::UBTTask_ClearBBValue(){
    NodeName = TEXT("Clear Blackboard Value");
}

EBTNodeResult::Type UBTTask_ClearBBValue::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) {
    Super::ExecuteTask(OwnerComp, NodeMemory);

    OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
    return EBTNodeResult::Succeeded;
}
