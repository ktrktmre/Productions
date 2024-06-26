/*==============================================================================

   �����Ǘ� [word.cpp]
														 Author :�ؓc �C���l
														 Date   :2023/09/14
--------------------------------------------------------------------------------

==============================================================================*/
#include "input.h"
#include "sprite.h"
#include "texture.h"
#include "myfunction.h"
#include "word.h"
#include "dictionary.h"
#include "player.h"
#include "score.h"
#include "fade.h"
#include "game.h"
#include "image.h"
#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define WORD_SIZE 50.0f
#define THEME_SIZE 100.0f
#define WORD_SPEED 2.0f
#define WORD_ROT_SPEED 10
#define DIRECTION_FRAME 360
#define RAIN_FRAME 90
#define CHAR_NUM 27
#define SHAPE_FRAME 60
#define SHAPE_SIZE 200
#define ALIGNMENT_NUMBER (WORD_NUM/4)
#define ALIGNMENT_INTERVAL (WORD_SIZE*3)
#define DIRECTION_CIRCLE_SIZE 400

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
WORDS g_Word[WORD_NUM];
D3DXVECTOR2 g_Pos[WORD_NUM];
GAME_MODE g_Gamemode;
std::string g_Theme;
int g_TexCircleID;
int g_TexCrossID;
int g_Frame;
int g_WordFrame;
int g_WordCount;
int g_WordIndex;
bool g_CircleFrag;
bool g_CrossFrag;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
std::string ThemeWord(void);
void TargetCharFull(void);
void TargetCharQuantity(int num, int index);
char SetChar(void);
void PositionInput(void);
D3DXVECTOR2 PositionOutputRandom(void);
D3DXVECTOR2 CharPosRandom(void);
D3DXVECTOR2 CharPosAlignment(int index);
void CharPosDirections(int part);
D3DXVECTOR2 CharPosition(D3DXVECTOR2 pos);
void SetGameMode(GAME_DIFF* pDiff);

//=============================================================================
// ����������
//=============================================================================
void InitWord(void)
{

	ID3D11Device* pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	g_TexCircleID = LoadTexture((char*)"data/TEXTURE/circle.png");
	g_TexCrossID = LoadTexture((char*)"data/TEXTURE/cross.png");

	//�����̏�����
	for (int wordCnt = 0; wordCnt < WORD_NUM; wordCnt++)
	{
		g_Word[wordCnt].pos = D3DXVECTOR2(0.0f, 0.0f);
		g_Word[wordCnt].size = D3DXVECTOR2(0.0f, 0.0f);
		g_Word[wordCnt].tex_v = D3DXVECTOR2(0.0f, 0.0f);
		g_Word[wordCnt].tex_f = D3DXVECTOR2(0.0f, 0.0f);
		g_Word[wordCnt].color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_Word[wordCnt].frame = 0;
		g_Word[wordCnt].chr = 0;
		g_Word[wordCnt].rot = 0;
		g_Word[wordCnt].rot_speed = 0;
		g_Word[wordCnt].coll = false;
		g_Word[wordCnt].use = false;

		g_Pos[wordCnt] = D3DXVECTOR2(0.0f, 0.0f);
	}
	g_Frame = 0;
	g_WordFrame = 0;
	g_CircleFrag = false;
	g_CrossFrag = false;
	g_WordCount = 0;
	g_WordIndex = 0;

	//�Q�[�����[�h�̏�����
	GAME_DIFF* pGameDiff = GetGameDiff();
	SetGameMode(pGameDiff);

	//����̏�����
	InitDictionary();
	g_Theme = ThemeWord();
	PositionInput();
}

//=============================================================================
// �I������
//=============================================================================
void UninitWord(void)
{
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateWord(void)
{
	SOUND_RECORD* pSoundRecord = GetSoundRecord();
	//�I����
	for (int wordCnt = 0; wordCnt < WORD_NUM; wordCnt++)
	{
		if (g_Word[wordCnt].use&&g_Word[wordCnt].coll)
		{
			PLAYER* pPlayer = GetPlayer();

			if (pPlayer->shoot)
			{
				if (g_Word[wordCnt].chr == g_Theme[g_WordIndex])
				{
					g_CircleFrag = true;
					g_WordIndex++;
					g_Word[wordCnt].use = false;
					PlaySound(pSoundRecord->SECorrectID, 0);
					SetScore(SUCCESS_POINT);
				}
				else
				{
					g_CrossFrag = true;
					PlaySound(pSoundRecord->SEWrongID, 0);
					SetScore(-SUCCESS_POINT / 2);
				}
			}
		}
	}

	//�����E�s����
	if (g_CircleFrag || g_CrossFrag)
	{
		g_Frame++;
		if (g_Frame >= SHAPE_FRAME)
		{
			g_Frame = 0;
			g_CircleFrag = false;
			g_CrossFrag = false;
		}
	}

	//���[�h��
	switch (g_Gamemode)
	{
	case ALIGNMENT:
		break;
	case ALIGNMENT_MOVE:
		//�ړ�
		for (int wordCnt = 0; wordCnt < WORD_NUM; wordCnt++)
		{
			if (g_Word[wordCnt].use)
			{
				g_Word[wordCnt].pos += g_Word[wordCnt].vel;

				if (g_Word[wordCnt].pos.x < SCREEN_WIDTH / 3 || g_Word[wordCnt].pos.x >(SCREEN_WIDTH / 3) * 2)
				{
					g_Word[wordCnt].vel.x *= -1;
				}
				if (g_Word[wordCnt].pos.y < SCREEN_HEIGHT / 3 || g_Word[wordCnt].pos.y >SCREEN_Q_HEIGHT * 3)
				{
					g_Word[wordCnt].vel.y *= -1;
				}
			}
		}
		break;
	case ALIGNMENT_ROTATE:
		//��]
		for (int wordCnt = 0; wordCnt < WORD_NUM; wordCnt++)
		{
			if (g_Word[wordCnt].use)
			{
				g_Word[wordCnt].rot += g_Word[wordCnt].rot_speed;

				//���]
				if (g_Word[wordCnt].rot >= D3DX_PI * 2 || g_Word[wordCnt].rot <= D3DX_PI * -2)
				{
					g_Word[wordCnt].rot = 0;
				}
			}
		}
		break;
	case ALIGNMENT_ROT_MOVE:
		//��]
		for (int wordCnt = 0; wordCnt < WORD_NUM; wordCnt++)
		{
			if (g_Word[wordCnt].use)
			{
				g_Word[wordCnt].rot += g_Word[wordCnt].rot_speed;

				//���]
				if (g_Word[wordCnt].rot >= D3DX_PI * 2 || g_Word[wordCnt].rot <= D3DX_PI * -2)
				{
					g_Word[wordCnt].rot = 0;
				}
			}
		}
		//�ړ�
		for (int wordCnt = 0; wordCnt < WORD_NUM; wordCnt++)
		{
			if (g_Word[wordCnt].use)
			{
				g_Word[wordCnt].pos += g_Word[wordCnt].vel;

				if (g_Word[wordCnt].pos.x < SCREEN_WIDTH / 3 || g_Word[wordCnt].pos.x >(SCREEN_WIDTH / 3) * 2)
				{
					g_Word[wordCnt].vel.x *= -1;
				}
				if (g_Word[wordCnt].pos.y < SCREEN_HEIGHT / 3 || g_Word[wordCnt].pos.y >SCREEN_Q_HEIGHT * 3)
				{
					g_Word[wordCnt].vel.y *= -1;
				}
			}
		}
		break;
	case DIRECTION:
		//�ړ�
		for (int wordCnt = 0; wordCnt < WORD_NUM; wordCnt++)
		{
			if (g_Word[wordCnt].use)
			{
				g_Word[wordCnt].pos += g_Word[wordCnt].vel;
			}
		}
		g_WordFrame++;
		//���X�^�[�g
		if (g_WordFrame >= DIRECTION_FRAME)
		{
			g_WordFrame = 0;
			for (int wordCnt = 0; wordCnt < WORD_NUM; wordCnt++)
			{
				g_Word[wordCnt].use = false;
			}
			PositionInput();
		}
		break;
	case FOUNTAIN:
		//�ړ�
		for (int wordCnt = 0; wordCnt < WORD_NUM; wordCnt++)
		{

			if (g_Word[wordCnt].use)
			{
				g_Word[wordCnt].pos += g_Word[wordCnt].vel;
				g_Word[wordCnt].vel.y += 0.1f;

				//���X�^�[�g
				if (g_Word[wordCnt].pos.y >= SCREEN_HEIGHT - 250)
				{
					//���W�̐ݒ�
					g_Word[wordCnt].pos = D3DXVECTOR2(SCREEN_H_WIDTH, SCREEN_HEIGHT - 300);
					//�ړ����x�̐ݒ�
					g_Word[wordCnt].vel.x = WORD_SPEED * RandPercent(100, 70) * PlusMinus();
					g_Word[wordCnt].vel.y = WORD_SPEED * 6 * RandPercent(90, 40) * -1;
				}
			}
		}
		break;
	case RAIN:
		//�ړ�
		for (int wordCnt = 0; wordCnt < WORD_NUM; wordCnt++)
		{
			if (g_Word[wordCnt].use)
			{
				g_Word[wordCnt].pos += g_Word[wordCnt].vel;

				//���X�^�[�g
				if (g_Word[wordCnt].pos.y >= SCREEN_HEIGHT - 250)
				{
					//���W�̐ݒ�
					g_Word[wordCnt].pos.y = 300;
					//�ړ����x�̐ݒ�
					g_Word[wordCnt].vel.y = WORD_SPEED * 3 * RandPercent(100, 20);
				}
			}
		}
		break;
	default:
		break;
	}

	//�N���A
	if (g_WordIndex == g_Theme.length())
	{
		InitWord();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawWord(void)
{
	SetSamplerState(FILTER_MODE_LINEAR, ADDRESS_MODE_WRAP);
	IMAGE* pImage = GetImage();

	//����̕`��
	//����̕�������������������
	if (EvenOdd(g_WordCount))
	{
		float center = (SCREEN_H_WIDTH) - (g_WordCount / 2 * THEME_SIZE);
		for (int wordCnt = 0; wordCnt < g_WordCount; wordCnt++)
		{
			char chr = g_Theme[wordCnt];
			//�������Ă��镶��
			if (g_WordIndex > wordCnt)
			{
				DrawChar(pImage->TexDefChrID, D3DXVECTOR2(center + (THEME_SIZE * wordCnt), 0.0f), &chr, THEME_SIZE, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
			}
			//�������Ă��Ȃ�����
			else
			{
				DrawChar(pImage->TexDefChrID, D3DXVECTOR2(center + (THEME_SIZE * wordCnt), 0.0f), &chr, THEME_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
		}
	}
	else
	{
		float center = (SCREEN_H_WIDTH) - ((float)g_WordCount / 2.0f * (float)THEME_SIZE);
		for (int wordCnt = 0; wordCnt < g_WordCount; wordCnt++)
		{
			char chr = g_Theme[wordCnt];
			//�������Ă��镶��
			if (g_WordIndex > wordCnt)
			{
				DrawChar(pImage->TexDefChrID, D3DXVECTOR2(center + (THEME_SIZE * wordCnt), 0.0f), &chr, THEME_SIZE, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
			}
			//�������Ă��Ȃ�����
			else
			{
				DrawChar(pImage->TexDefChrID, D3DXVECTOR2(center + (THEME_SIZE * wordCnt), 0.0f), &chr, THEME_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
		}
	}
	//�I�̕`��
	for (int wordCnt = 0; wordCnt < WORD_NUM; wordCnt++)
	{
		if(g_Word[wordCnt].use)
		DrawCharRot(pImage->TexDefChrID, g_Word[wordCnt].pos, &g_Word[wordCnt].chr, WORD_SIZE, g_Word[wordCnt].color,g_Word[wordCnt].rot);
	}

	//�������̕`��
	if (g_CircleFrag)
	{
		DrawSpriteColor(g_TexCircleID, D3DXVECTOR2(SCREEN_H_WIDTH, SCREEN_H_HEIGHT),
			D3DXVECTOR2(SHAPE_SIZE, SHAPE_SIZE), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f),
			D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
	}

	//�s�������̕`��
	if (g_CrossFrag)
	{
		DrawSpriteColor(g_TexCrossID, D3DXVECTOR2(SCREEN_H_WIDTH, SCREEN_H_HEIGHT),
			D3DXVECTOR2(SHAPE_SIZE, SHAPE_SIZE), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f),
			D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	}
}

//=============================================================================
// Word�Q�b�^�[�֐�
//=============================================================================
WORDS* GetWord(void)
{
	return g_Word;
}

//=============================================================================
// Word�Z�b�^�[�֐�
//=============================================================================
void SetWord(D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXCOLOR color, char chr)
{
	for (int wordCnt = 0; wordCnt < WORD_NUM; wordCnt++)
	{
		if (!g_Word[wordCnt].use)
		{
			g_Word[wordCnt].pos = pos;
			g_Word[wordCnt].size = size;
			g_Word[wordCnt].chr = chr;
			g_Word[wordCnt].tex_v = D3DXVECTOR2(0.0f, 0.0f);
			g_Word[wordCnt].tex_f = D3DXVECTOR2(TEX_PART(4), 1.0f);
			g_Word[wordCnt].color = color;
			g_Word[wordCnt].use = true;
			break;
		}
	}
}

//=============================================================================
// ����̐ݒ�
//=============================================================================
std::string ThemeWord(void)
{
	DICTIONARY* pDictionary = GetDictionary();
	int num = 0;
	for (int dictCnt = 0; dictCnt < DICTIONARY_NUM; dictCnt++)
	{
		if (!pDictionary[dictCnt].use)
		{
			break;
		}
		else
		{
			num++;
		}
	}

	if (num == 0)
	{
		return "none";
	}
	else
	{
		return pDictionary[rand() % num].word;
	}
}

//=============================================================================
// �I�ɂȂ镶���̐ݒ�:�󂫔z��S��
//=============================================================================
void TargetCharFull(void)
{
	//����̕������̎擾
	g_WordCount = g_Theme.length();

	//����̕����̎擾
	for (int wordCnt = 0; wordCnt < g_WordCount; wordCnt++)
	{
		SetWord(PositionOutputRandom(), D3DXVECTOR2(WORD_SIZE, WORD_SIZE), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), g_Theme[wordCnt]);
	}

	//�t�F�C�N�����̃Z�b�g
	for (int wordCnt = g_WordCount; wordCnt < WORD_NUM; wordCnt++)
	{
		SetWord(PositionOutputRandom(), D3DXVECTOR2(WORD_SIZE, WORD_SIZE), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), SetChar());
	}
}

//=============================================================================
// �I�ɂȂ镶���̐ݒ�:���w��
//=============================================================================
void TargetCharQuantity(int num, int index)
{
	//����̕������̎擾
	g_WordCount = g_Theme.length();
	int randNum = rand() % num;

	//����̕����̃Z�b�g
	SetWord(g_Pos[randNum], D3DXVECTOR2(WORD_SIZE, WORD_SIZE), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), g_Theme[index]);
	g_Pos[randNum] = D3DXVECTOR2(0, 0);

	//�t�F�C�N�����̃Z�b�g
	for (int wordCnt = 0; wordCnt < num-1; wordCnt++)
	{
		randNum = rand() % num;
		while (g_Pos[randNum].x==0)
		{
			randNum++;
			if (randNum >= num)
			{
				randNum = 0;
			}
		}
		SetWord(g_Pos[randNum], D3DXVECTOR2(WORD_SIZE, WORD_SIZE), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), SetChar());
		g_Pos[randNum] = D3DXVECTOR2(0, 0);
	}
}

//=============================================================================
// �����̃Z�b�g
//=============================================================================
char SetChar(void)
{
	//�����̌��
	char alpha[CHAR_NUM] = {
		"a""b""c""d""e""f""g"
		"h""i""j""k""l""m""n"
		"o""p""q""r""s""t""u"
		"v""w""x""y""z"
	};

	//�����̃Z�b�g
	char chr = alpha[rand() % (CHAR_NUM - 1)];

	return chr;
}

//=============================================================================
// ���W�̓���
//=============================================================================
void PositionInput(void)
{
	switch (g_Gamemode)
	{
	case ALIGNMENT:
		for (int wordCnt = 0; wordCnt < WORD_NUM; wordCnt++)
		{
			//���W�̐ݒ�
			g_Pos[wordCnt] = CharPosAlignment(wordCnt);
		}
		TargetCharFull();
		break;
	case ALIGNMENT_MOVE:
		for (int wordCnt = 0; wordCnt < WORD_NUM; wordCnt++)
		{
			//���W�̐ݒ�
			g_Pos[wordCnt] = CharPosAlignment(wordCnt);
			//�ړ����x�̐ݒ�
			g_Word[wordCnt].vel.x = WORD_SPEED * RandPercent(100, 0) * PlusMinus();
			g_Word[wordCnt].vel.y = WORD_SPEED * RandPercent(100, 0) * PlusMinus();
		}
		TargetCharFull();
		break;
	case ALIGNMENT_ROTATE:
		for (int wordCnt = 0; wordCnt < WORD_NUM; wordCnt++)
		{
			//���W�̐ݒ�
			g_Pos[wordCnt] = CharPosAlignment(wordCnt);
			//��]���x�̐ݒ�
			g_Word[wordCnt].rot_speed = D3DXToRadian(WORD_ROT_SPEED * RandPercent(100, 0)) * PlusMinus();
		}
		TargetCharFull();
		break;
	case ALIGNMENT_ROT_MOVE:
		for (int wordCnt = 0; wordCnt < WORD_NUM; wordCnt++)
		{
			//���W�̐ݒ�
			g_Pos[wordCnt] = CharPosAlignment(wordCnt);
			//�ړ����x�̐ݒ�
			g_Word[wordCnt].vel.x = WORD_SPEED * RandPercent(100, 0)* PlusMinus();
			g_Word[wordCnt].vel.y = WORD_SPEED * RandPercent(100, 0)* PlusMinus();
			//��]���x�̐ݒ�
			g_Word[wordCnt].rot_speed = D3DXToRadian(WORD_ROT_SPEED * RandPercent(100, 0)) * PlusMinus();
		}
		TargetCharFull();
		break;
	case DIRECTION:
		//���W�̐ݒ�
		CharPosDirections(WORD_NUM);
		TargetCharFull();
		for (int wordCnt = 0; wordCnt < WORD_NUM; wordCnt++)
		{
			//�ړ����x�̐ݒ�
			g_Word[wordCnt].vel.x = cosf(atan2f(g_Word[wordCnt].pos.y - SCREEN_H_HEIGHT, g_Word[wordCnt].pos.x - SCREEN_H_WIDTH)) * WORD_SPEED * -1;
			g_Word[wordCnt].vel.y = sinf(atan2f(g_Word[wordCnt].pos.y - SCREEN_H_HEIGHT, g_Word[wordCnt].pos.x - SCREEN_H_WIDTH)) * WORD_SPEED * -1;
		}
		break;
	case FOUNTAIN:
		for (int wordCnt = 0; wordCnt < WORD_NUM; wordCnt++)
		{
			//���W�̐ݒ�
			g_Pos[wordCnt] = CharPosition(D3DXVECTOR2(SCREEN_H_WIDTH, SCREEN_HEIGHT - 300));
			//�ړ����x�̐ݒ�
			g_Word[wordCnt].vel.x = WORD_SPEED * RandPercent(100, 70) * PlusMinus();
			g_Word[wordCnt].vel.y = WORD_SPEED * 6 * RandPercent(90, 40) * -1;
		}
		TargetCharFull();
		break;
	case RAIN:
		for (int wordCnt = 0; wordCnt < WORD_NUM; wordCnt++)
		{
			if (wordCnt % 5 == 0)
			{
				//���W�̐ݒ�
				g_Pos[wordCnt] = CharPosition(D3DXVECTOR2(SCREEN_H_WIDTH - 300, SCREEN_Q_HEIGHT));
			}
			else if (wordCnt % 5 == 1)
			{
				//���W�̐ݒ�
				g_Pos[wordCnt] = CharPosition(D3DXVECTOR2(SCREEN_H_WIDTH - 150, SCREEN_Q_HEIGHT));
			}
			else if (wordCnt % 5 == 2)
			{
				//���W�̐ݒ�
				g_Pos[wordCnt] = CharPosition(D3DXVECTOR2(SCREEN_H_WIDTH, SCREEN_Q_HEIGHT));
			}
			else if (wordCnt % 5 == 3)
			{
				//���W�̐ݒ�
				g_Pos[wordCnt] = CharPosition(D3DXVECTOR2(SCREEN_H_WIDTH + 150, SCREEN_Q_HEIGHT));
			}
			else
			{
				//���W�̐ݒ�
				g_Pos[wordCnt] = CharPosition(D3DXVECTOR2(SCREEN_H_WIDTH + 300, SCREEN_Q_HEIGHT));
			}
			//�ړ����x�̐ݒ�
			g_Word[wordCnt].vel.x = 0;
			g_Word[wordCnt].vel.y = WORD_SPEED * 3 * RandPercent(100, 20);
		}
		TargetCharFull();
		break;
	default:
		break;
	}
}

//=============================================================================
// ���W�̏o��:�����_��
//=============================================================================
D3DXVECTOR2 PositionOutputRandom(void)
{
	int num = rand() % WORD_NUM;

	while (g_Pos[num].x==0)
	{
		num++;
		if (num >= WORD_NUM)
		{
			num = 0;
		}
	}

	D3DXVECTOR2 pos = g_Pos[num];
	g_Pos[num] = D3DXVECTOR2(0.0f, 0.0f);

	return pos;
}


//=============================================================================
// ���W�̐ݒ�:�����_��
//=============================================================================
D3DXVECTOR2 CharPosRandom(void)
{
	//�I�̐����͈�
	int ScreenRangeWidth = SCREEN_WIDTH / 3;
	int ScreenRangeHeight = SCREEN_HEIGHT / 3;

	//�I�̍��W(�����͈͓��Ń����_���ȍ��W*���Ԃ肠��)
	D3DXVECTOR2 randPos = D3DXVECTOR2((rand() % ScreenRangeWidth) + ScreenRangeWidth,
		(rand() % ScreenRangeHeight) + ScreenRangeHeight);

	return randPos;
}

//=============================================================================
// ���W�̐ݒ�:����
//=============================================================================
D3DXVECTOR2 CharPosAlignment(int index)
{
	//�I�̐����͈�
	int ScreenRangeWidth = SCREEN_WIDTH / 3;
	int ScreenRangeHeight = SCREEN_HEIGHT / 3;

	//�I�̍��W(�����͈͓��Ő��񂵂����W*���Ԃ�Ȃ�)
	D3DXVECTOR2 alignPos = D3DXVECTOR2(ScreenRangeWidth + ALIGNMENT_INTERVAL * (index % ALIGNMENT_NUMBER),
		ScreenRangeHeight + ALIGNMENT_INTERVAL * (index / ALIGNMENT_NUMBER));

	return alignPos;
}

//=============================================================================
// ���W�̐ݒ�:n����
//=============================================================================
void CharPosDirections(int part)
{
	//�I�̍��W(��ʂ̐^�񒆂𒆐S�Ƃ����~���w�肵�����ɕ������A�U�蕪����)
	for (int wordCnt = 0; wordCnt < part; wordCnt++)
	{
		int direct = wordCnt % part;
		direct *= 360 / part;
		D3DXVECTOR2 directPos = D3DXVECTOR2(SCREEN_H_WIDTH, SCREEN_H_HEIGHT);
		directPos.x += DIRECTION_CIRCLE_SIZE * cosf(D3DXToRadian(direct));
		directPos.y += DIRECTION_CIRCLE_SIZE * sinf(D3DXToRadian(direct));

		g_Pos[wordCnt] = directPos;
	}

}

//=============================================================================
// ���W�̐ݒ�:���W�w��
//=============================================================================
D3DXVECTOR2 CharPosition(D3DXVECTOR2 pos)
{
	//�I�̍��W
	return pos;
}

//=============================================================================
// �Q�[�����[�h�Z�b�^�[
//=============================================================================
void SetGameMode(GAME_DIFF* pDiff)
{
	int mode;
	switch (*pDiff)
	{
	case NORMAL:
		mode = rand() % NORMAL_MODE_NUM;
		if (mode == 0)
			g_Gamemode = ALIGNMENT;
		else if (mode == 1)
			g_Gamemode = ALIGNMENT_ROTATE;
		else if (mode == 2)
			g_Gamemode = DIRECTION;
		else
			g_Gamemode = RAIN;
		break;
	case HARD:
		mode = rand() % HARD_MODE_NUM;
		if (mode == 0)
			g_Gamemode = ALIGNMENT_MOVE;
		else if (mode == 1)
			g_Gamemode = ALIGNMENT_ROT_MOVE;
		else if (mode == 2)
			g_Gamemode = DIRECTION;
		else if (mode == 3)
			g_Gamemode = FOUNTAIN;
		else
			g_Gamemode = RAIN;
		break;
	default:
		mode = rand() % GAME_MODE_NUM;
		if (mode == 0)
			g_Gamemode = ALIGNMENT;
		else if (mode == 1)
			g_Gamemode = ALIGNMENT_MOVE;
		else if (mode == 2)
			g_Gamemode = ALIGNMENT_ROTATE;
		else if (mode == 3)
			g_Gamemode = ALIGNMENT_ROT_MOVE;
		else if (mode == 4)
			g_Gamemode = DIRECTION;
		else if (mode == 5)
			g_Gamemode = FOUNTAIN;
		else
			g_Gamemode = RAIN;
		break;
	}
}