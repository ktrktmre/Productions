//=============================================================================
//
// �G�f�ޏ��� [material.cpp]
// Author : �ؓc�C���l
//
//=============================================================================
#include "main.h"
#include "material.h"
#include "Texture.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
Model_Material g_Model_Material;
Image_Material g_Image_Material;

//=============================================================================
// ����������
//=============================================================================
void RegisterMaterial(void)
{
	//obj���f���̓ǂݍ���
	LoadModel((char*)"data/MODEL/sphere.obj", &g_Model_Material.m_Sphere);
	LoadModel((char*)"data/MODEL/torus.obj", &g_Model_Material.m_Torus);
	LoadModel((char*)"data/MODEL/fallen_tree.obj", &g_Model_Material.m_Tree);
	LoadModel((char*)"data/MODEL/crystal.obj", &g_Model_Material.m_Crystal);
	LoadModel((char*)"data/MODEL/heart.obj", &g_Model_Material.m_Heart);
	LoadModel((char*)"data/MODEL/skateboard.obj", &g_Model_Material.m_Skateboard);

	//�摜�̓ǂݍ���
	g_Image_Material.m_White= LoadTexture((char*)"data/TEXTURE/white.png");
	g_Image_Material.m_GameTitle = LoadTexture((char*)"data/TEXTURE/gametitle.png");
	g_Image_Material.m_Title= LoadTexture((char*)"data/TEXTURE/title.png");
	g_Image_Material.m_Rule= LoadTexture((char*)"data/TEXTURE/rule.png");
	g_Image_Material.m_Operation= LoadTexture((char*)"data/TEXTURE/operation .png");
	g_Image_Material.m_Shadow= LoadTexture((char*)"data/TEXTURE/shadow000.jpg");
	g_Image_Material.m_Lane= LoadTexture((char*)"data/TEXTURE/lane.png");
	g_Image_Material.m_SkyNight = LoadTexture((char*)"data/TEXTURE/dark_night.png");
	g_Image_Material.m_Mountain = LoadTexture((char*)"data/TEXTURE/mountain001.png");
	g_Image_Material.m_ExplosionBule = LoadTexture((char*)"data/TEXTURE/pipo-btleffect182_480.png");
	g_Image_Material.m_StarGreen = LoadTexture((char*)"data/TEXTURE/pipo-mapeffect011d.png");
	g_Image_Material.m_Disappear = LoadTexture((char*)"data/TEXTURE/pipo-btleffect010.png");
	g_Image_Material.m_Parry = LoadTexture((char*)"data/TEXTURE/pipo-btleffect180_480.png");
	g_Image_Material.m_Tornado = LoadTexture((char*)"data/TEXTURE/pipo-btleffect009.png");
	g_Image_Material.m_Lightning = LoadTexture((char*)"data/TEXTURE/lightning.png");
	g_Image_Material.m_BauNumber = LoadTexture((char*)"data/TEXTURE/bau_number.png");
	g_Image_Material.m_Play = LoadTexture((char*)"data/TEXTURE/play.png");
	g_Image_Material.m_Next = LoadTexture((char*)"data/TEXTURE/next.png");
	g_Image_Material.m_Explanation = LoadTexture((char*)"data/TEXTURE/explanation.png");
	g_Image_Material.m_Score = LoadTexture((char*)"data/TEXTURE/score.png");
	g_Image_Material.m_Return = LoadTexture((char*)"data/TEXTURE/return.png");
	g_Image_Material.m_Cursor = LoadTexture((char*)"data/TEXTURE/cursor.png");
	g_Image_Material.m_Frame = LoadTexture((char*)"data/TEXTURE/frame.png");
	g_Image_Material.m_Wall = LoadTexture((char*)"data/TEXTURE/dark_night_wall.png");
	g_Image_Material.m_HpGauge = LoadTexture((char*)"data/TEXTURE/Hp-gauge.png");
	g_Image_Material.m_AvoidGauge = LoadTexture((char*)"data/TEXTURE/Avoid-Gauge.png");
}

//=============================================================================
// �I������
//=============================================================================
void ReleaseMaterial(void)
{
	//�I������
	//obj���f���̉��
	UnloadModel(&g_Model_Material.m_Sphere);
	UnloadModel(&g_Model_Material.m_Torus);
	UnloadModel(&g_Model_Material.m_Tree);
	UnloadModel(&g_Model_Material.m_Crystal);
	UnloadModel(&g_Model_Material.m_Heart);
	UnloadModel(&g_Model_Material.m_Skateboard);
}

//=============================================================================
// ���f���\���̂̃Q�b�^�[
//=============================================================================
Model_Material& RefModelMaterial(void)
{
	return g_Model_Material;
}

//=============================================================================
// �C���[�W�\���̂̃Q�b�^�[
//=============================================================================
Image_Material& RefImageMaterial(void)
{
	return g_Image_Material;
}