#include "Mario.h"
#include <SJRendererAnimation.h>

void Mario::SetAnimation()
{
	m_AniRenderer->CreateAnimation(L"Small_Idle_Right", L"SmallMario_Right.bmp", 0, 0);
	m_AniRenderer->CreateAnimation(L"Small_SlowRun_Right", L"SmallMario_Right.bmp", 1, 0, 0.03f);
	m_AniRenderer->CreateAnimation(L"Small_SlowJump_Right", L"SmallMario_Right.bmp", 2, 2);
	m_AniRenderer->CreateAnimation(L"Small_FastRun_Right", L"SmallMario_Right.bmp", 4, 3, 0.01f);
	m_AniRenderer->CreateAnimation(L"Small_FastJump_Right", L"SmallMario_Right.bmp", 5, 5);
	m_AniRenderer->CreateAnimation(L"Small_Skid_Right", L"SmallMario_Right.bmp", 6, 6);
	m_AniRenderer->CreateAnimation(L"Small_In_Right", L"SmallMario_Right.bmp", 7, 7);
	m_AniRenderer->CreateAnimation(L"Small_CarryIdle_Right", L"SmallMario_Right.bmp", 8, 8);
	m_AniRenderer->CreateAnimation(L"Small_CarryRun_Right", L"SmallMario_Right.bmp", 9, 8, 0.03f);
	m_AniRenderer->CreateAnimation(L"Small_CarryJump_Right", L"SmallMario_Right.bmp", 9, 9);
	m_AniRenderer->CreateAnimation(L"Small_Kick_Right", L"SmallMario_Right.bmp", 10, 10);
	m_AniRenderer->CreateAnimation(L"Small_Slide_Right", L"SmallMario_Right.bmp", 11, 11);
	m_AniRenderer->CreateAnimation(L"Small_SwimmingIdle_Right", L"SmallMario_Right.bmp", 12, 13, 0.15f);
	m_AniRenderer->CreateAnimation(L"Small_SwimmingKick_Right", L"SmallMario_Right.bmp", 14, 15);

	m_AniRenderer->CreateAnimation(L"Small_Idle_Left", L"SmallMario_Left.bmp", 0, 0);
	m_AniRenderer->CreateAnimation(L"Small_SlowRun_Left", L"SmallMario_Left.bmp", 1, 0, 0.03f);
	m_AniRenderer->CreateAnimation(L"Small_SlowJump_Left", L"SmallMario_Left.bmp", 2, 2);
	m_AniRenderer->CreateAnimation(L"Small_FastRun_Left", L"SmallMario_Left.bmp", 4, 3, 0.01f);
	m_AniRenderer->CreateAnimation(L"Small_FastJump_Left", L"SmallMario_Left.bmp", 5, 5);
	m_AniRenderer->CreateAnimation(L"Small_Skid_Left", L"SmallMario_Left.bmp", 6, 6);
	m_AniRenderer->CreateAnimation(L"Small_In_Left", L"SmallMario_Left.bmp", 7, 7);
	m_AniRenderer->CreateAnimation(L"Small_CarryIdle_Left", L"SmallMario_Left.bmp", 8, 8);
	m_AniRenderer->CreateAnimation(L"Small_CarryRun_Left", L"SmallMario_Left.bmp", 9, 8, 0.03f);
	m_AniRenderer->CreateAnimation(L"Small_CarryJump_Left", L"SmallMario_Left.bmp", 9, 9);
	m_AniRenderer->CreateAnimation(L"Small_Kick_Left", L"SmallMario_Left.bmp", 10, 10);
	m_AniRenderer->CreateAnimation(L"Small_Slide_Left", L"SmallMario_Right.bmp", 11, 11);
	m_AniRenderer->CreateAnimation(L"Small_SwimmingIdle_Left", L"SmallMario_Left.bmp", 12, 13, 0.15f);
	m_AniRenderer->CreateAnimation(L"Small_SwimmingKick_Left", L"SmallMario_Left.bmp", 14, 15);

	m_AniRenderer->CreateAnimation(L"Small_Dead_Left", L"SmallMario_Right.bmp", 18, 18);
	m_AniRenderer->CreateAnimation(L"Small_Dead_Right", L"SmallMario_Right.bmp", 18, 18);

	m_AniRenderer->CreateAnimation(L"Small_Climb", L"SmallMario_Right.bmp", 16, 17, 0.15f);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// SuperMario

	m_AniRenderer->CreateAnimation(L"Super_Idle_Right", L"SuperMario_Right.bmp", 0, 0);
	m_AniRenderer->CreateAnimation(L"Super_SlowRun_Right", L"SuperMario_Right.bmp", 0, 3, 0.03f);
	m_AniRenderer->CreateAnimation(L"Super_Sit_Right", L"SuperMario_Right.bmp", 4, 4);
	m_AniRenderer->CreateAnimation(L"Super_SlowJump_Right", L"SuperMario_Right.bmp", 5, 5);
	m_AniRenderer->CreateAnimation(L"Super_SlowFall_Right", L"SuperMario_Right.bmp", 2, 2);
	m_AniRenderer->CreateAnimation(L"Super_FastRun_Right", L"SuperMario_Right.bmp", 6, 9, 0.01f);
	m_AniRenderer->CreateAnimation(L"Super_FastJump_Right", L"SuperMario_Right.bmp", 10, 10);
	m_AniRenderer->CreateAnimation(L"Super_Skid_Right", L"SuperMario_Right.bmp", 11, 11);
	m_AniRenderer->CreateAnimation(L"Super_In_Right", L"SuperMario_Right.bmp", 12, 12);
	m_AniRenderer->CreateAnimation(L"Super_CarryIdle_Right", L"SuperMario_Right.bmp", 14, 14);
	m_AniRenderer->CreateAnimation(L"Super_CarryRun_Right", L"SuperMario_Right.bmp", 14, 17, 0.03f);
	m_AniRenderer->CreateAnimation(L"Super_CarryJump_Right", L"SuperMario_Right.bmp", 16, 16);
	m_AniRenderer->CreateAnimation(L"Super_Kick_Right", L"SuperMario_Right.bmp", 18, 18);
	m_AniRenderer->CreateAnimation(L"Super_Slide_Right", L"SuperMario_Right.bmp", 19, 19);
	m_AniRenderer->CreateAnimation(L"Super_SwimmingIdle_Right", L"SuperMario_Right.bmp", 20, 20);
	m_AniRenderer->CreateAnimation(L"Super_SwimmingKick_Right", L"SuperMario_Right.bmp", 21, 23, 0.15f);
	m_AniRenderer->CreateAnimation(L"Super_Change_Right", L"SuperMario_Right.bmp", 25, 25);

	m_AniRenderer->CreateAnimation(L"Super_Idle_Left", L"SuperMario_Left.bmp", 0, 0);
	m_AniRenderer->CreateAnimation(L"Super_SlowRun_Left", L"SuperMario_Left.bmp", 0, 3, 0.03f);
	m_AniRenderer->CreateAnimation(L"Super_Sit_Left", L"SuperMario_Left.bmp", 4, 4);
	m_AniRenderer->CreateAnimation(L"Super_SlowJump_Left", L"SuperMario_Left.bmp", 5, 5);
	m_AniRenderer->CreateAnimation(L"Super_SlowFall_Left", L"SuperMario_Left.bmp", 2, 2);
	m_AniRenderer->CreateAnimation(L"Super_FastRun_Left", L"SuperMario_Left.bmp", 6, 9, 0.01f);
	m_AniRenderer->CreateAnimation(L"Super_FastJump_Left", L"SuperMario_Left.bmp", 10, 10);
	m_AniRenderer->CreateAnimation(L"Super_Skid_Left", L"SuperMario_Left.bmp", 11, 11);
	m_AniRenderer->CreateAnimation(L"Super_In_Left", L"SuperMario_Left.bmp", 12, 12);
	m_AniRenderer->CreateAnimation(L"Super_CarryIdle_Left", L"SuperMario_Left.bmp", 14, 14);
	m_AniRenderer->CreateAnimation(L"Super_CarryRun_Left", L"SuperMario_Left.bmp", 14, 17, 0.03f);
	m_AniRenderer->CreateAnimation(L"Super_CarryJump_Left", L"SuperMario_Left.bmp", 16, 16);
	m_AniRenderer->CreateAnimation(L"Super_Kick_Left", L"SuperMario_Left.bmp", 18, 18);
	m_AniRenderer->CreateAnimation(L"Super_Slide_Left", L"SuperMario_Left.bmp", 19, 19);
	m_AniRenderer->CreateAnimation(L"Super_SwimmingIdle_Left", L"SuperMario_Left.bmp", 20, 20);
	m_AniRenderer->CreateAnimation(L"Super_SwimmingKick_Left", L"SuperMario_Left.bmp", 21, 23, 0.15f);
	m_AniRenderer->CreateAnimation(L"Super_Change_Left", L"SuperMario_Left.bmp", 25, 25);

	m_AniRenderer->CreateAnimation(L"Super_Climb_Left", L"SuperMario_Left.bmp", 24, 24);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// RacoonMario


	m_AniRenderer->CreateAnimation(L"Racoon_Change_Left", L"RacoonChange.bmp", 0, 5, 0.05f);
	m_AniRenderer->CreateAnimation(L"Racoon_Change_Right", L"RacoonChange.bmp", 6, 11, 0.05f);

	m_AniRenderer->CreateAnimation(L"Racoon_Idle_Left", L"RacoonMario_Left.bmp", 0, 0);
	m_AniRenderer->CreateAnimation(L"Racoon_SlowRun_Left", L"RacoonMario_Left.bmp", 0, 3, 0.03f);
	m_AniRenderer->CreateAnimation(L"Racoon_Sit_Left", L"RacoonMario_Left.bmp", 4, 4);
	m_AniRenderer->CreateAnimation(L"Racoon_SlowJump_Left", L"RacoonMario_Left.bmp", 33, 33);
	m_AniRenderer->CreateAnimation(L"Racoon_SlowFall_Left", L"RacoonMario_Left.bmp", 7, 7);
	m_AniRenderer->CreateAnimation(L"Racoon_SlowTail_Left", L"RacoonMario_Left.bmp", 5, 7);
	m_AniRenderer->CreateAnimation(L"Racoon_FastRun_Left", L"RacoonMario_Left.bmp", 8, 11, 0.01f);
	m_AniRenderer->CreateAnimation(L"Racoon_FastJump_Left", L"RacoonMario_Left.bmp", 14, 14);
	m_AniRenderer->CreateAnimation(L"Racoon_FastFall_Left", L"RacoonMario_Left.bmp", 12, 12);
	m_AniRenderer->CreateAnimation(L"Racoon_FastTail_Left", L"RacoonMario_Left.bmp", 12, 14);
	m_AniRenderer->CreateAnimation(L"Racoon_Skid_Left", L"RacoonMario_Left.bmp", 15, 15);
	m_AniRenderer->CreateAnimation(L"Racoon_In_Left", L"RacoonMario_Left.bmp", 17, 17);
	m_AniRenderer->CreateAnimation(L"Racoon_TailAttack_Left", L"RacoonMario_Left.bmp", 16, 20, 0.03f);
	m_AniRenderer->CreateAnimation(L"Racoon_CarryIdle_Left", L"RacoonMario_Left.bmp", 21, 21);
	m_AniRenderer->CreateAnimation(L"Racoon_CarryRun_Left", L"RacoonMario_Left.bmp", 21, 24, 0.03f);
	m_AniRenderer->CreateAnimation(L"Racoon_CarryJump_Left", L"RacoonMario_Left.bmp", 23, 23);
	m_AniRenderer->CreateAnimation(L"Racoon_Kick_Left", L"RacoonMario_Left.bmp", 25, 25);
	m_AniRenderer->CreateAnimation(L"Racoon_Slide_Left", L"RacoonMario_Left.bmp", 26, 26);
	m_AniRenderer->CreateAnimation(L"Racoon_SwimmingIdle_Left", L"RacoonMario_Left.bmp", 27, 29, 0.15f);
	m_AniRenderer->CreateAnimation(L"Racoon_SwimmingKick_Left", L"RacoonMario_Left.bmp", 30, 30);

	m_AniRenderer->CreateAnimation(L"Racoon_Idle_Right", L"RacoonMario_Right.bmp", 0, 0);
	m_AniRenderer->CreateAnimation(L"Racoon_SlowRun_Right", L"RacoonMario_Right.bmp", 0, 3, 0.03f);
	m_AniRenderer->CreateAnimation(L"Racoon_Sit_Right", L"RacoonMario_Right.bmp", 4, 4);
	m_AniRenderer->CreateAnimation(L"Racoon_SlowJump_Right", L"RacoonMario_Right.bmp", 33, 33);
	m_AniRenderer->CreateAnimation(L"Racoon_SlowFall_Right", L"RacoonMario_Right.bmp", 7, 7);
	m_AniRenderer->CreateAnimation(L"Racoon_SlowTail_Right", L"RacoonMario_Right.bmp", 5, 7);
	m_AniRenderer->CreateAnimation(L"Racoon_FastRun_Right", L"RacoonMario_Right.bmp", 8, 11, 0.01f);
	m_AniRenderer->CreateAnimation(L"Racoon_FastJump_Right", L"RacoonMario_Right.bmp", 14, 14);
	m_AniRenderer->CreateAnimation(L"Racoon_FastFall_Right", L"RacoonMario_Right.bmp", 12, 12);
	m_AniRenderer->CreateAnimation(L"Racoon_FastTail_Right", L"RacoonMario_Right.bmp", 12, 14);
	m_AniRenderer->CreateAnimation(L"Racoon_Skid_Right", L"RacoonMario_Right.bmp", 15, 15);
	m_AniRenderer->CreateAnimation(L"Racoon_In_Right", L"RacoonMario_Right.bmp", 17, 17);
	m_AniRenderer->CreateAnimation(L"Racoon_TailAttack_Right", L"RacoonMario_Right.bmp", 16, 20, 0.03f);
	m_AniRenderer->CreateAnimation(L"Racoon_CarryIdle_Right", L"RacoonMario_Right.bmp", 21, 21);
	m_AniRenderer->CreateAnimation(L"Racoon_CarryRun_Right", L"RacoonMario_Right.bmp", 21, 24, 0.03f);
	m_AniRenderer->CreateAnimation(L"Racoon_CarryJump_Right", L"RacoonMario_Right.bmp", 23, 23);
	m_AniRenderer->CreateAnimation(L"Racoon_Kick_Right", L"RacoonMario_Right.bmp", 25, 25);
	m_AniRenderer->CreateAnimation(L"Racoon_Slide_Right", L"RacoonMario_Right.bmp", 26, 26);
	m_AniRenderer->CreateAnimation(L"Racoon_SwimmingIdle_Right", L"RacoonMario_Right.bmp", 27, 29, 0.15f);
	m_AniRenderer->CreateAnimation(L"Racoon_SwimmingKick_Right", L"RacoonMario_Right.bmp", 30, 30);

	m_AniRenderer->CreateAnimation(L"Racoon_Climb_Right", L"RacoonMario_Right.bmp", 31, 32);
}
