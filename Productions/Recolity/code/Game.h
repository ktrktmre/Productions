#pragma once
#include "main.h"
#include "bullet_interface.h"
#include "player.h"
#include "enemy_management.h"
enum StageScelect
{
	Tutorial,
	Stage1,
	Stage2,
};
enum Gamemode
{
	Easy,
	Nomal,
	Hard,
};

void InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);

void Emitta(int n, D3DXVECTOR3 pos);
Bullet_Interface* GetBulletInterface();
void SetDamageText(int Damage, D3DXVECTOR3 pos, D3DXCOLOR coler);
PLAYER* GetPlayer();
Enemy_Management* GetEnemymanager();
void SetStageScelect(StageScelect s);
StageScelect GetStageSelect();
void SetGamemode(Gamemode mode);
Gamemode GetGamemode();