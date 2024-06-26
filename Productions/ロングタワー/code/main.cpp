//============================================
// CP11 No.09 ネームバトラー
// author 切田海畝斗 作成開始日:2022/12/12
//                   最終更新日;2022/1/12
//============================================
//=============================
// インクルード
//=============================
#include "conioex.h" 
#include<time.h>
//=============================
// マクロ定義
//=============================
#define MAX_PLAYER (4)
#define JOB_MAX (4)
#define NAME_MAX (17)
#define ATTRIBUTE_MAX (4)
#define MAX_SKILL (5)
#define MAX_RETENTION_SKILL (3)
#define MAX_BOSS (4)
#define CHEAT_JOB "ファイター"
#define CHEAT_JOB_NUM (1)
//=============================
// 列挙体宣言
//=============================
enum {//モード識別番号
	debug = 0,
	summon,
	wait,
	del,
	explore,
	save,
	load,
	exi,
	cheat=10,
};
enum {//ジョブ識別番号
	fighterNum = 1,
	tankNum,
	wizardNum,
	assassinNum,
};
enum {//属性識別番号
	fire = 1,
	thunder,
	soil,
	normal,
	/*火は雷に強い、雷は土に強い、土は火に強い*/
};
enum {
	kaenzan = 0,
	raimeizan,
	daitigiri,
	kaen,
	raigeki,
	rakuseki,
	kitou,
	kiaitame,
	maryokutame,
	gougeki,
	goutai,
	tujigkiri,
	hosifuri,
};
enum {//スキル識別番号
	skill1 = 0,
	skill2,
	skill3,
	skill4,
	skill5,
};
enum {
	enemyIdenNum=0,
	bossIdenNum,
	playerIdenNum,
};
enum {
	αNum=0,
	βNum,
	εNum,
	ΩNum,
};
//=============================
// 構造体宣言
//=============================
typedef struct {
	char OPAA[7][91];
}TITLE;
typedef struct {
	char NAME[NAME_MAX];
	char JOB[NAME_MAX];
	char ATTRIBUTE[ATTRIBUTE_MAX];
	int ATTRIBUTE_NUM;
	int LEVEL;
	int LIFE;
	int SIKLL_POINT;
	int ATK;
	int DEF;
	int MATK;
	int MDEF;
	int SPD;
	int LUCK;
	int IDEN;
	int JOBNUM;
	int EXP;
	int BOSSIDEN;
}STATUS;
typedef struct {
	char SKILL_NAME[NAME_MAX];
	char SKILL_ATTRIBUTE[ATTRIBUTE_MAX];
	int SKILL_DEL;
	int SKILL_AT_NUM;
	int SKILL_IDEN_NUM;
}SKILL_STUCK;
typedef struct {
	char ITEM_NAME[NAME_MAX];
	int ITEM_LIFE;
	int ITEM_ATK;
	int ITEM_DEF;
	int ITEM_MATK;
	int ITEM_MDEF;
	int ITEM_SPD;
	int ITEM_LUCK;
}ITEM_STUCK;
//=============================
// グローバル変数
//=============================
//=============================
// プロトタイプ宣言
//=============================
void clear();
void data(STATUS* pPlayer, int* pX, int* pY);
void createPlayer(STATUS* pPlayer, int* pX, int* pY);
void createPlayerCheat(STATUS* pPlayer, int* pCheatSel);
void createEnemy(STATUS* pEnemy, STATUS* pPlayer, int* pExSel);
void createBoss(STATUS* pBoss, STATUS* pPlayer, STATUS* pEnemy, int* pExSel);
void viewPlayer(STATUS* pPlayer, int* pX, int* pY);
void viewEnemy(STATUS* pEnemy);
void deletePlayer(STATUS* pPlayer, int* pX, int* pY);
void deleteEnemy(STATUS* pEnemy);
void savePlayer(STATUS* pPlayer, int* pX, int* pY);
void loadPlayer(STATUS* pPlayer, int* pX, int* pY);
void explorePlayer(STATUS* pPlayer, STATUS* pEnemy, STATUS* pBoss, int* pX, int* pY, int* pSizeX, int* pSizeY, bool* pCut);
void battle(STATUS* pPlayer, STATUS* pEnemy, SKILL_STUCK* pSkill, ITEM_STUCK* pItem, int* pSkillCount, int* pExSel, int* pDefeat, int* pX, int* pY);
void action(STATUS* pAttacker, SKILL_STUCK* pSkill, STATUS* pDefender, int* pDamage, int* pPhyFrag, int* pMagFrag, int* pLuckLimit, int* pDefLimit, int* pBuff, int* pX, int* pY, int* pCritFrag, int* pPlayerMaxLife, int* pEnemyMaxLife, int* pSkillSel);
void battleView(STATUS* pAttacker, STATUS* pDefender, int* pX, int* pY, int* pPlayerMaxLife, int* pEnemyMaxLife);
void levelUp(STATUS* pPlayer, SKILL_STUCK* pSkill, int* pSkillCount, int* pExSel, int* pX, int* pY);
void skillFighter(SKILL_STUCK* pSkill, int* pSkillCount, int* pX, int* pY);
void skillTank(SKILL_STUCK* pSkill, int* pSkillCount, int* pX, int* pY);
void skillWizard(SKILL_STUCK* pSkill, int* pSkillCount, int* pX, int* pY);
void skillAssassin(SKILL_STUCK* pSkill, int* pSkillCount, int* pX, int* pY);
void skillEnemy(STATUS* pAttacker, STATUS* pDefender, SKILL_STUCK* pSkill, int* pEnemyDamage, int* pBuff, int* pEnemyLuckLimit, int* pEnemyDefLimit, int* pPhyEFrag, int* pMagEFrag, int* pX, int* pY, int* pCritFrag);
void viewSkill(SKILL_STUCK* pSkill, int* pX, int* pY);
void object(ITEM_STUCK* pItem, STATUS* pPlayer, int* pExSel, int* pX, int* pY);
void dungeonEscape(int* pEscape, int* pStair, int* pX, int* pY);
//=============================
// 画面サイズ
//=============================
BOOL controlSize(int x, int y) {
	HANDLE hStdout;
	COORD coord;
	coord.X = x;
	coord.Y = y;

	SMALL_RECT rectConsoleSize;
	rectConsoleSize.Left = 0;
	rectConsoleSize.Top = 0;
	rectConsoleSize.Right = 1;
	rectConsoleSize.Bottom = 1;

	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	// 一度コンソール表示サイズを小さくする
	SetConsoleWindowInfo(hStdout, TRUE, &rectConsoleSize);

	// バッファサイズを目的の大きさに設定する
	if (!SetConsoleScreenBufferSize(hStdout, coord)) {
		return FALSE;
	}

	// ウィンドウサイズを目的の大きさに設定にする
	rectConsoleSize.Right = x - 1;
	rectConsoleSize.Bottom = y - 1;
	SetConsoleWindowInfo(hStdout, TRUE, &rectConsoleSize);
	return TRUE;
}
//=============================
// メイン関数
//=============================
int main(void)
{
	TITLE titleOp = {};
	FILE* fp;
	STATUS player[MAX_PLAYER] = {};
	STATUS enemy = {};
	STATUS boss[MAX_BOSS] = {};
	bool cut;
	int mode = 0;
	int x = 0, y = 0;
	int sizeX = 0, sizeY = 0;
	fp = fopen("op\\opAA.txt", "r");
	fread(&titleOp, sizeof(TITLE), 1, fp);
	fclose(fp);
	sizeX = 90, sizeY = 15;
	controlSize(sizeX, sizeY);
	gotoxy(1, 5);
	printf("%s", titleOp);
	y = wherey();
	gotoxy(1, y + 4);
	printf("PRESS ENTER!");
	clear();
	sizeX = 110, sizeY = 30;
	controlSize(sizeX, sizeY);
	while (1)
	{
		//モード選択開始//
		gotoxy(15, 5);
		x = wherex();
		printf("|召喚[1]　待機所[2]　解雇[3]　探検[4]　セーブ[5]　ロード[6]　帰還[7]\n");
		y = wherey();
		data(player,&x,&y);
		gotoxy(x, y);
		printf("＞");
		scanf("%d",&mode);
		if (mode == summon)//キャラクター生成
		{
			rewind(stdin);
			system("cls");
			x = 15, y = 5;
			viewPlayer(player,&x,&y);//キャラクター表示
			createPlayer(player, &x, &y);
			rewind(stdin);
			system("cls");
		}
		else if (mode == wait)//キャラクター表示
		{
			rewind(stdin);
			system("cls");
			x = 15, y = 5;
			viewPlayer(player,&x,&y);
			clear();
		}
		else if (mode == del)//キャラクター削除
		{
			rewind(stdin);
			system("cls");
			x = 15, y = 5;
			viewPlayer(player, &x, &y);
			deletePlayer(player,&x,&y);
			clear();
		}
		else if (mode == explore)//探索
		{
			rewind(stdin);
			system("cls");
			explorePlayer(player, &enemy, boss, &x, &y, &sizeX, &sizeY, &cut);
			if (cut = true)
			{
				rewind(stdin);
				system("cls");
			}
			else
			{
				clear();
			}
			sizeX = 100, sizeY = 30;
			controlSize(sizeX, sizeY);
		}
		else if (mode == save)//キャラクターセーブ(外部ファイル)
		{
			rewind(stdin);
			system("cls");
			x = 15, y = 5;
			viewPlayer(player, &x, &y);
			savePlayer(player,&x,&y);
			clear();
		}
		else if (mode == load)//キャラクターロード(外部ファイル)
		{
			rewind(stdin);
			system("cls");
			loadPlayer(player, &x, &y);
			clear();
		}
		else if (mode == exi)//ゲーム終了
		{
			break;
		}
		else if (mode == cheat)//デバック用ゲームキャラクター生成
		{
			int cheatSel = 0;
			printf("?＞");
			scanf("%d", &cheatSel);
			cheatSel--;
			createPlayerCheat(player,&cheatSel);
			rewind(stdin);
			system("cls");
		}
	}
	rewind(stdin);
	getchar();
	return 0;
}
//=============================
// 画面クリア
//=============================
void clear()
{
	rewind(stdin);
	getchar();
	system("cls");
}
//=============================
// エンプティデータ
//=============================
void data(STATUS* pPlayer, int* pX, int* pY)
{
	gotoxy(*pX, *pY);
	printf("|待機状況");
	//空きデータの表示//
	for (int i = 0; i < MAX_PLAYER; i++)
	{
		if ((pPlayer + i)->NAME[0] != '\0')//名前の入力有無
		{
			printf("[●]");//データ有
		}
		else
		{
			printf("[〇]");//データ無
		}
	}
	printf("|");
	printf("\n");
	*pY = wherey();
}
//=============================
// ステータス生成:プレイヤー
//=============================
void createPlayer(STATUS* pPlayer, int* pX, int* pY)
{
	STATUS prePlayer = {};//ステータス仮入用→データを保存する場所を選択できるようにするため
	int word = 0, randUp = 0, room = 0;
	while (1)
	{
		gotoxy(*pX, *pY);
		printf("名前を入力してください(ひらがな1～8文字以内)＞");
		scanf("%s", prePlayer.NAME);
		*pY = *pY + 1;
		word = strlen(prePlayer.NAME) / 2;//名前の長さを計測→名前の長さからステータスを生成するため(マルチバイト文字にも対応できるようにしているので割る2している)
		if (word >= 9)
		{
			gotoxy(*pX, *pY);
			printf("8文字以内でどうか\n");
			*pY = wherey();
		}
		else
			break;
	}
	prePlayer.JOBNUM = word % JOB_MAX + 1;
	srand((unsigned int)time(NULL));
	if (prePlayer.JOBNUM == fighterNum)
	{
		strcpy(prePlayer.JOB, "ファイター");//体力、攻撃力、スピードが高くなりやすく、魔力、魔防が低い
		randUp = (word % 2 + 1) * (rand() % 10 + 1);
		prePlayer.LIFE = ((rand() % 51 + 50) + randUp);
		randUp = (word % 2 + 1) * (rand() % 10 + 1);
		prePlayer.ATK = ((rand() % 51 + 50) + randUp);
		prePlayer.DEF = (rand() % 51 + 50);
		prePlayer.MATK = (rand() % 51 + 30);
		prePlayer.MDEF = (rand() % 51 + 30);
		randUp = (word % 2 + 1) * (rand() % 10 + 1);
		prePlayer.SPD = ((rand() % 51 + 50) + randUp);
		prePlayer.LUCK = (rand() % 51 + 50);
	}
	else if (prePlayer.JOBNUM == tankNum)
	{
		strcpy(prePlayer.JOB, "タンク");//体力、防御力、魔防が高くなりやすく、スピード、魔力が低い
		randUp = (word % 2 + 1) * (rand() % 10 + 1);
		prePlayer.LIFE = ((rand() % 51 + 50) + randUp);
		prePlayer.ATK = (rand() % 51 + 50);
		randUp = (word % 2 + 1) * (rand() % 10 + 1);
		prePlayer.DEF = ((rand() % 51 + 50) + randUp);
		prePlayer.MATK = (rand() % 51 + 30);
		randUp = (word % 2 + 1) * (rand() % 10 + 1);
		prePlayer.MDEF = ((rand() % 51 + 50) + randUp);
		prePlayer.SPD = (rand() % 51 + 30);
		prePlayer.LUCK = (rand() % 51 + 50);
	}
	else if (prePlayer.JOBNUM == wizardNum)
	{
		strcpy(prePlayer.JOB, "ウィザード");//魔力、魔防、運が高くなりやすく、攻撃力、防御力が低い
		prePlayer.LIFE = (rand() % 51 + 50);
		prePlayer.ATK = (rand() % 51 + 30);
		prePlayer.DEF = (rand() % 51 + 30);
		randUp = (word % 2 + 1) * (rand() % 10 + 1);
		prePlayer.MATK = ((rand() % 51 + 50) + randUp);
		randUp = (word % 2 + 1) * (rand() % 10 + 1);
		prePlayer.MDEF = ((rand() % 51 + 50) + randUp);
		prePlayer.SPD = (rand() % 51 + 50);
		randUp = (word % 2 + 1) * (rand() % 10 + 1);
		prePlayer.LUCK = ((rand() % 51 + 50) + randUp);
	}
	else if (prePlayer.JOBNUM == assassinNum)
	{
		strcpy(prePlayer.JOB, "アサシン");//攻撃力、魔力、スピードが高くなりやすく、体力、運が低い
		prePlayer.LIFE = (rand() % 51 + 30);
		randUp = (word % 2 + 1) * (rand() % 10 + 1);
		prePlayer.ATK = ((rand() % 51 + 50) + randUp);
		prePlayer.DEF = (rand() % 51 + 50);
		randUp = (word % 2 + 1) * (rand() % 10 + 1);
		prePlayer.MATK = ((rand() % 51 + 50) + randUp);
		prePlayer.MDEF = (rand() % 51 + 50);
		randUp = (word % 2 + 1) * (rand() % 10 + 1);
		prePlayer.SPD = ((rand() % 51 + 50) + randUp);
		prePlayer.LUCK = (rand() % 51 + 30);
	}
	prePlayer.LEVEL = 1;
	prePlayer.SIKLL_POINT = rand() % 51 + 20;
	prePlayer.ATTRIBUTE_NUM = rand() % ATTRIBUTE_MAX + 1;
	if (prePlayer.ATTRIBUTE_NUM == fire)
	{
		strcpy(prePlayer.ATTRIBUTE,"火");
	}
	else if (prePlayer.ATTRIBUTE_NUM == thunder)
	{
		strcpy(prePlayer.ATTRIBUTE, "雷");
	}
	else if (prePlayer.ATTRIBUTE_NUM == soil)
	{
		strcpy(prePlayer.ATTRIBUTE, "土");
	}
	else if (prePlayer.ATTRIBUTE_NUM == normal)
	{
		strcpy(prePlayer.ATTRIBUTE, "無");
	}
	prePlayer.IDEN = playerIdenNum;//プレイヤーとエネミー識別番号(エネミー:0 ボス:1 プレイヤー:2)
	gotoxy(*pX, *pY);
	printf("何号室に待機してもらいますか？(半角数字)＞");
	scanf("%d",&room);
	(pPlayer[room - 1]) = prePlayer;//選択したデータ場所に生成したステータスをコピー
}
//=========================================
// ステータス生成:プレイヤー(デバック用)
//========================================
void createPlayerCheat(STATUS* pPlayer,int* pCheatSel)
{
	strcpy((pPlayer + *pCheatSel)->NAME, "テスト");
	strcpy((pPlayer + *pCheatSel)->JOB, CHEAT_JOB);
	strcpy((pPlayer + *pCheatSel)->ATTRIBUTE, "無");
	(pPlayer + *pCheatSel)->ATTRIBUTE_NUM = normal;
	(pPlayer + *pCheatSel)->LEVEL = 100;
	(pPlayer + *pCheatSel)->LIFE = 1000;
	(pPlayer + *pCheatSel)->ATK = 10;
	(pPlayer + *pCheatSel)->DEF = 1000;
	(pPlayer + *pCheatSel)->MATK = 100;
	(pPlayer + *pCheatSel)->MDEF = 1000;
	(pPlayer + *pCheatSel)->SPD = 1000;
	(pPlayer + *pCheatSel)->LUCK = 1000;
	(pPlayer + *pCheatSel)->SIKLL_POINT = 1000;
	(pPlayer + *pCheatSel)->JOBNUM = CHEAT_JOB_NUM;
	(pPlayer + *pCheatSel)->IDEN = playerIdenNum;
}
//=============================
// ステータス生成:エネミー
//=============================
void createEnemy(STATUS* pEnemy, STATUS* pPlayer, int* pExSel)
{
	int randNum = 0, randUp = 0;
	srand((unsigned int)time(NULL));
	//エネミーネーム決定//
	if (rand() % 100 < 20)
	{
		strcpy(pEnemy->NAME, "ゾンビ");
	}
	else if (rand() % 100 >= 20 && rand() % 100 < 40)
	{
		strcpy(pEnemy->NAME, "スライム");
	}
	else if (rand() % 100 >= 40 && rand() % 100 < 60)
	{
		strcpy(pEnemy->NAME, "スケルトン");
	}
	else if (rand() % 100 >= 60 && rand() % 100 < 80)
	{
		strcpy(pEnemy->NAME, "バンディット");
	}
	else if (rand() % 100 >= 80 && rand() % 100 < 90)
	{
		strcpy(pEnemy->NAME, "からくりきし");
	}
	else
	{
		strcpy(pEnemy->NAME, "りゅうきし");
	}
	pEnemy->JOBNUM = (rand() % JOB_MAX) + 1;
	pEnemy->LEVEL = (pPlayer + *pExSel)->LEVEL;
	if (pEnemy->JOBNUM == fighterNum)
	{
		strcpy(pEnemy->JOB, "ファイター");//体力、攻撃力、スピードが高くなりやすく、魔力、魔防が低い
		randUp = (rand() % 2 + 1) * (rand() % 10 + 1);
		pEnemy->LIFE = (((rand() % 51 + 40) + randUp) + ((rand() % 10 + 1) * pEnemy->LEVEL));
		randUp = (rand() % 2 + 1) * (rand() % 10 + 1);
		pEnemy->ATK = (((rand() % 51 + 40) + randUp) +  ((rand() % 10 + 1) * pEnemy->LEVEL));
		pEnemy->DEF = ((rand() % 51 + 40) +  ((rand() % 10 + 1) * pEnemy->LEVEL));
		pEnemy->MATK = ((rand() % 51 + 30) +  ((rand() % 10 + 1) * pEnemy->LEVEL));
		pEnemy->MDEF = ((rand() % 51 + 30) +  ((rand() % 10 + 1) * pEnemy->LEVEL));
		randUp = (rand() % 2 + 1) * (rand() % 10 + 1);
		pEnemy->SPD = (((rand() % 51 + 40) + randUp) +  ((rand() % 10 + 1) * pEnemy->LEVEL));
		pEnemy->LUCK = (rand() % 51 + 50);
	}
	else if (pEnemy->JOBNUM == tankNum)
	{
		strcpy(pEnemy->JOB, "タンク");//体力、防御力、魔防が高くなりやすく、スピード、魔力が低い
		randUp = (rand() % 2 + 1) * (rand() % 10 + 1);
		pEnemy->LIFE = (((rand() % 51 + 40) + randUp) +  ((rand() % 10 + 1) * pEnemy->LEVEL));
		pEnemy->ATK = ((rand() % 51 + 40) +  ((rand() % 10 + 1) * pEnemy->LEVEL));
		randUp = (rand() % 2 + 1) * (rand() % 10 + 1);
		pEnemy->DEF = (((rand() % 51 + 40) + randUp) +  ((rand() % 10 + 1) * pEnemy->LEVEL));
		pEnemy->MATK = ((rand() % 51 + 30) +  ((rand() % 10 + 1) * pEnemy->LEVEL));
		randUp = (rand() % 2 + 1) * (rand() % 10 + 1);
		pEnemy->MDEF = (((rand() % 51 + 40) + randUp) +  ((rand() % 10 + 1) * pEnemy->LEVEL));
		pEnemy->SPD = ((rand() % 51 + 30) +  ((rand() % 10 + 1) * pEnemy->LEVEL));
		pEnemy->LUCK = (rand() % 51 + 50);
	}
	else if (pEnemy->JOBNUM == wizardNum)
	{
		strcpy(pEnemy->JOB, "ウィザード");//魔力、魔防、運が高くなりやすく、攻撃力、防御力が低い
		pEnemy->LIFE = ((rand() % 51 + 40) +  ((rand() % 10 + 1) * pEnemy->LEVEL));
		pEnemy->ATK = ((rand() % 51 + 30) +  ((rand() % 10 + 1) * pEnemy->LEVEL));
		pEnemy->DEF = ((rand() % 51 + 30) +  ((rand() % 10 + 1) * pEnemy->LEVEL));
		randUp = (rand() % 2 + 1) * (rand() % 10 + 1);
		pEnemy->MATK = (((rand() % 51 + 40) + randUp) +  ((rand() % 10 + 1) * pEnemy->LEVEL));
		randUp = (rand() % 2 + 1) * (rand() % 10 + 1);
		pEnemy->MDEF = (((rand() % 51 + 40) + randUp) +  ((rand() % 10 + 1) * pEnemy->LEVEL));
		pEnemy->SPD = ((rand() % 51 + 40) +  ((rand() % 10 + 1) * pEnemy->LEVEL));
		randUp = (rand() % 2 + 1) * (rand() % 10 + 1);
		pEnemy->LUCK = ((rand() % 51 + 50) + randUp);
	}
	else if (pEnemy->JOBNUM == assassinNum)
	{
		strcpy(pEnemy->JOB, "アサシン");//攻撃力、魔力、スピードが高くなりやすく、体力、運が低い
		pEnemy->LIFE = ((rand() % 51 + 30) +  ((rand() % 10 + 1) * pEnemy->LEVEL));
		randUp = (rand() % 2 + 1) * (rand() % 10 + 1);
		pEnemy->ATK = (((rand() % 51 + 40) + randUp) +  ((rand() % 10 + 1) * pEnemy->LEVEL));
		pEnemy->DEF = ((rand() % 51 + 40) +  ((rand() % 10 + 1) * pEnemy->LEVEL));
		randUp = (rand() % 2 + 1) * (rand() % 10 + 1);
		pEnemy->MATK = (((rand() % 51 + 40) + randUp) +  ((rand() % 10 + 1) * pEnemy->LEVEL));
		pEnemy->MDEF = ((rand() % 51 + 40) +  ((rand() % 10 + 1) * pEnemy->LEVEL));
		randUp = (rand() % 2 + 1) * (rand() % 10 + 1);
		pEnemy->SPD = (((rand() % 51 + 40) + randUp) +  ((rand() % 10 + 1) * pEnemy->LEVEL));
		pEnemy->LUCK = (rand() % 51 + 30);
	}
	pEnemy->SIKLL_POINT = (rand() % 51 + 20) + ((rand() % pEnemy->LEVEL + 1) * (rand() % 2 + 1));
	pEnemy->ATTRIBUTE_NUM = rand() % ATTRIBUTE_MAX + 1;
	if (pEnemy->ATTRIBUTE_NUM == fire)
	{
		strcpy(pEnemy->ATTRIBUTE, "火");
	}
	else if (pEnemy->ATTRIBUTE_NUM == thunder)
	{
		strcpy(pEnemy->ATTRIBUTE, "雷");
	}
	else if (pEnemy->ATTRIBUTE_NUM == soil)
	{
		strcpy(pEnemy->ATTRIBUTE, "土");
	}
	else if (pEnemy->ATTRIBUTE_NUM == normal)
	{
		strcpy(pEnemy->ATTRIBUTE, "無");
	}
	pEnemy->IDEN = enemyIdenNum;//プレイヤーとエネミー識別番号(エネミー:0 ボス:1 プレイヤー:2)
}//=============================
// ステータス生成:ボス
//=============================
void createBoss(STATUS* pBoss, STATUS* pPlayer, STATUS* pEnemy, int* pExSel)
{
	//プレイヤーの現在のステータスを参照し生成//
	int bossNum = αNum;
	srand((unsigned int)time(NULL));
	strcpy((pBoss+bossNum)->NAME,"α");
	strcpy((pBoss+bossNum)->JOB,"タンク");
	strcpy((pBoss+bossNum)->ATTRIBUTE,"火");
	(pBoss + bossNum)->ATTRIBUTE_NUM = fire;
	(pBoss + bossNum)->LEVEL = (pPlayer + *pExSel)->LEVEL;
	(pBoss + bossNum)->LIFE = (pPlayer + *pExSel)->LIFE * 2;
	(pBoss + bossNum)->ATK = (pPlayer + *pExSel)->ATK * 0.9f;
	(pBoss + bossNum)->DEF = (pPlayer + *pExSel)->DEF * 1.2f;
	(pBoss + bossNum)->MATK = (pPlayer + *pExSel)->MATK * 0.8f;
	(pBoss + bossNum)->MDEF = (pPlayer + *pExSel)->MDEF * 0.8f;
	(pBoss + bossNum)->SPD = (pPlayer + *pExSel)->SPD - 1;
	(pBoss + bossNum)->LUCK = 50;
	(pBoss + bossNum)->JOBNUM = tankNum;
	(pBoss + bossNum)->IDEN = bossIdenNum;
	(pBoss + bossNum)->BOSSIDEN = αNum;
	bossNum = βNum;
	strcpy((pBoss + bossNum)->NAME, "β");
	strcpy((pBoss + bossNum)->JOB, "アサシン");
	strcpy((pBoss + bossNum)->ATTRIBUTE, "雷");
	(pBoss + bossNum)->ATTRIBUTE_NUM = thunder;
	(pBoss + bossNum)->LEVEL = (pPlayer + *pExSel)->LEVEL;
	(pBoss + bossNum)->LIFE = (pPlayer + *pExSel)->LIFE * 0.7f;
	(pBoss + bossNum)->ATK = (pPlayer + *pExSel)->ATK * 1.2f;
	(pBoss + bossNum)->DEF = (pPlayer + *pExSel)->DEF * 0.7f;
	(pBoss + bossNum)->MATK = (pPlayer + *pExSel)->MATK * 1.5f;
	(pBoss + bossNum)->MDEF = (pPlayer + *pExSel)->MDEF * 0.8f;
	(pBoss + bossNum)->SPD = (pPlayer + *pExSel)->SPD *1.3;
	(pBoss + bossNum)->LUCK = 50;
	(pBoss + bossNum)->JOBNUM = assassinNum;
	(pBoss + bossNum)->IDEN = bossIdenNum;
	(pBoss + bossNum)->BOSSIDEN = βNum;
	bossNum = εNum;
	strcpy((pBoss + bossNum)->NAME, "ε");
	strcpy((pBoss + bossNum)->JOB, "ウィザード");
	strcpy((pBoss + bossNum)->ATTRIBUTE, "土");
	(pBoss + bossNum)->ATTRIBUTE_NUM = soil;
	(pBoss + bossNum)->LEVEL = (pPlayer + *pExSel)->LEVEL;
	(pBoss + bossNum)->LIFE = (pPlayer + *pExSel)->LIFE * 0.8f;
	(pBoss + bossNum)->ATK = (pPlayer + *pExSel)->ATK * 0.5f;
	(pBoss + bossNum)->DEF = (pPlayer + *pExSel)->DEF*0.7f;
	(pBoss + bossNum)->MATK = (pPlayer + *pExSel)->MATK * 1.5f;
	(pBoss + bossNum)->MDEF = (pPlayer + *pExSel)->MDEF * 1.3f;
	(pBoss + bossNum)->SPD = (pPlayer + *pExSel)->SPD - 1;
	(pBoss + bossNum)->LUCK = 50;
	(pBoss + bossNum)->JOBNUM = wizardNum;
	(pBoss + bossNum)->IDEN = bossIdenNum;
	(pBoss + bossNum)->BOSSIDEN = εNum;
	bossNum = ΩNum;
	strcpy((pBoss + bossNum)->NAME, "Ω-0");
	strcpy((pBoss + bossNum)->JOB, "ファイター");
	strcpy((pBoss + bossNum)->ATTRIBUTE, "無");
	(pBoss + bossNum)->ATTRIBUTE_NUM = normal;
	(pBoss + bossNum)->LEVEL = (pPlayer + *pExSel)->LEVEL;
	(pBoss + bossNum)->LIFE = (pPlayer + *pExSel)->LIFE * 2;
	(pBoss + bossNum)->ATK = (pPlayer + *pExSel)->ATK * 1.5f;
	(pBoss + bossNum)->DEF = (pPlayer + *pExSel)->DEF * 1.1f;
	(pBoss + bossNum)->MATK = (pPlayer + *pExSel)->MATK * 1.2f;
	(pBoss + bossNum)->MDEF = (pPlayer + *pExSel)->MDEF * 1.2f;
	if (rand() % 2 == 1)
	{
		(pBoss + bossNum)->SPD = (pPlayer + *pExSel)->SPD + 1;
	}
	else
	{
		(pBoss + bossNum)->SPD = (pPlayer + *pExSel)->SPD - 1;
	}
	(pBoss + bossNum)->LUCK = 80;
	(pBoss + bossNum)->JOBNUM = fighterNum;
	(pBoss + bossNum)->IDEN = bossIdenNum; //プレイヤーとエネミー識別番号(エネミー:0 ボス:1 プレイヤー:2)
	(pBoss + bossNum)->BOSSIDEN = ΩNum;
}
//=============================
// ステータス表示:プレイヤー
//=============================
void viewPlayer(STATUS* pPlayer, int* pX, int* pY)
{
	//プレイヤーステータスの表示//
	for (int i = 0; i < MAX_PLAYER; i++)
	{
		gotoxy(*pX, *pY);
		printf("%d号室", i + 1);
		if ((pPlayer + i)->NAME[0] != '\0')
		{
			gotoxy(*pX, *pY+1);
			printf("【%s :lv %d:性質 %s】:%s\n", (pPlayer + i)->NAME, (pPlayer + i)->LEVEL, (pPlayer + i)->ATTRIBUTE, (pPlayer + i)->JOB);
			*pY = wherey();
			gotoxy(*pX, *pY);
			printf("【体力:%d　攻撃力%d　防御力%d　魔力%d　魔防%d　素早さ%d　運%d SP:%d】\n\n", (pPlayer + i)->LIFE, (pPlayer + i)->ATK, (pPlayer + i)->DEF, (pPlayer + i)->MATK, (pPlayer + i)->MDEF, (pPlayer + i)->SPD, (pPlayer + i)->LUCK, (pPlayer + i)->SIKLL_POINT);
			*pY = wherey();
		}
		else
		{
			printf("～NO DATA～\n\n\n");
			*pY = wherey();
		}
	}
	gotoxy(*pX, *pY);
	printf("▽");
}
//==========================================
// ステータス表示:エネミー(デバック用)
//==========================================
void viewEnemy(STATUS* pEnemy)
{
	//エネミーステータスの表示//
	printf("【%s :lv%d :性質%s】:%s\n【体力:%d　SP:%d　攻撃力%d　防御力%d　魔力%d　魔防%d　素早さ%d　運%d】\n\n\n", pEnemy->NAME, pEnemy->LEVEL, pEnemy->ATTRIBUTE, pEnemy->JOB, pEnemy->LIFE, pEnemy->SIKLL_POINT, pEnemy->ATK, pEnemy->DEF, pEnemy->MATK, pEnemy->MDEF, pEnemy->SPD, pEnemy->LUCK);
}
//=============================
// ステータス削除:プレイヤー
//=============================
void deletePlayer(STATUS* pPlayer, int* pX, int* pY)
{
	int delSel = 0, judge = 0;
	gotoxy(*pX, *pY);
	printf("解雇する兵士を選んでください＞");
	scanf("%d",&delSel);//削除する兵士の番号指定
	delSel--;
	*pY = (*pY + 1);
	//ステータスデータの有無//
	if ((pPlayer + delSel)->NAME[0] != '\0')
	{
		gotoxy(*pX, *pY);
		printf("本当に解雇しますか？(はい:1/いいえ:2)＞");
		*pY = (*pY + 1);
		scanf("%d", &judge);
		//プレイヤーステータスデータの削除(初期化)
		if (judge == 1)
		{
			(pPlayer + delSel)->NAME[0] = '\0';
			(pPlayer + delSel)->JOB[0] = '\0';
			(pPlayer + delSel)->ATTRIBUTE[0] = '\0';
			(pPlayer + delSel)->ATTRIBUTE_NUM = 0;
			(pPlayer + delSel)->JOBNUM = 0;
			(pPlayer + delSel)->LIFE = 0;
			(pPlayer + delSel)->SIKLL_POINT = 0;
			(pPlayer + delSel)->ATK = 0;
			(pPlayer + delSel)->DEF = 0;
			(pPlayer + delSel)->MATK = 0;
			(pPlayer + delSel)->MDEF = 0;
			(pPlayer + delSel)->SPD = 0;
			(pPlayer + delSel)->LUCK = 0;
			(pPlayer + delSel)->IDEN = 0;
			gotoxy(*pX, *pY);
			printf("解雇しました▽");
		}
		else if (judge == 2)
		{
			gotoxy(*pX, *pY);
			printf("%sは嬉しそうに部屋に戻っていった▽", (pPlayer + delSel)->NAME);
		}
	}
	else
	{
		gotoxy(*pX, *pY + 1);
		printf("中に誰もいませんよ...？▽");
	}
}
//=============================
// ステータス削除:エネミー
//=============================
void deleteEnemy(STATUS* pEnemy)
{
	//エネミーステータスデータの削除(初期化)
	pEnemy->NAME[0] = '\0';
	pEnemy->JOB[0] = '\0';
	pEnemy->ATTRIBUTE[0] = '\0';
	pEnemy->ATTRIBUTE_NUM = 0;
	pEnemy->JOBNUM = 0;
	pEnemy->LIFE = 0;
	pEnemy->SIKLL_POINT = 0;
	pEnemy->ATK = 0;
	pEnemy->DEF = 0;
	pEnemy->MATK = 0;
	pEnemy->MDEF = 0;
	pEnemy->SPD = 0;
	pEnemy->LUCK = 0;
}
//=============================
// ステータスセーブ:プレイヤー
//=============================
void savePlayer(STATUS* pPlayer, int* pX, int* pY)
{
	STATUS playerData[MAX_PLAYER] = {};
	FILE* fp;
	int saveNum = 0, playerNum = 0, dataNum = 0;
	gotoxy(*pX, *pY);
	printf("セーブする兵士を選択してください＞");
	scanf("%d", &saveNum);
	rewind(stdin);
	system("cls");
	*pY = 5;
	//セーブデータの有無(外部ファイルの入力状況)//
	fp = fopen("savedata\\soldier1.txt", "r");
	fread((playerData + playerNum), sizeof(STATUS), 1, fp);
	fclose(fp);
	playerNum++;
	fp = fopen("savedata\\soldier2.txt", "r");
	fread((playerData + playerNum), sizeof(STATUS), 1, fp);
	fclose(fp);
	playerNum++;
	fp = fopen("savedata\\soldier3.txt", "r");
	fread((playerData + playerNum), sizeof(STATUS), 1, fp);
	fclose(fp);
	playerNum++;
	fp = fopen("savedata\\soldier4.txt", "r");
	fread((playerData + playerNum), sizeof(STATUS), 1, fp);
	fclose(fp);
	viewPlayer(playerData, pX, pY);
	gotoxy(*pX, *pY);
	printf("どのセーブデータに入れますか＞");
	scanf("%d", &dataNum);//セーブするファイルの指定
	*pY = *pY + 1;
	//セーブする外部ファイルの選択//
	if (dataNum >= 1 && dataNum <= 4)
	{
		saveNum--;
		if (dataNum == 1)
		{
			fp = fopen("savedata\\soldier1.txt", "w");
			fwrite((pPlayer + saveNum), sizeof(STATUS), 1, fp);
			fclose(fp);
		}
		else if (dataNum == 2)
		{
			fp = fopen("savedata\\soldier2.txt", "w");
			fwrite((pPlayer + saveNum), sizeof(STATUS), 1, fp);
			fclose(fp);
		}
		else if (dataNum == 3)
		{
			fp = fopen("savedata\\soldier3.txt", "w");
			fwrite((pPlayer + saveNum), sizeof(STATUS), 1, fp);
			fclose(fp);
		}
		else if (dataNum == 4)
		{
			fp = fopen("savedata\\soldier4.txt", "w");
			fwrite((pPlayer + saveNum), sizeof(STATUS), 1, fp);
			fclose(fp);
		}
		gotoxy(*pX, *pY);
		printf("セーブ完了しました▽");
	}
	else
	{
		gotoxy(*pX, *pY);
		printf("セーブ出来ませんでした▽");
	}
}
//=============================
// ステータスロード:プレイヤー
//=============================
void loadPlayer(STATUS* pPlayer, int* pX, int* pY)
{
	STATUS playerData[MAX_PLAYER] = {};
	FILE* fp;
	int loadNum = 0, playerNum = 0, dataNum = 0;
	//セーブデータの有無(外部ファイルの入力状況)//
	fp = fopen("savedata\\soldier1.txt", "r");
	fread((playerData + playerNum), sizeof(STATUS), 1, fp);
	fclose(fp);
	playerNum++;
	fp = fopen("savedata\\soldier2.txt", "r");
	fread((playerData + playerNum), sizeof(STATUS), 1, fp);
	fclose(fp);
	playerNum++;
	fp = fopen("savedata\\soldier3.txt", "r");
	fread((playerData + playerNum), sizeof(STATUS), 1, fp);
	fclose(fp);
	playerNum++;
	fp = fopen("savedata\\soldier4.txt", "r");
	fread((playerData + playerNum), sizeof(STATUS), 1, fp);
	fclose(fp);
	*pY = 5;
	viewPlayer(playerData, pX, pY);
	gotoxy(*pX, *pY);
	printf("ロードする兵士を選択してください＞");
	scanf("%d", &loadNum);//外部ファイルからロードする兵士データの指定
	rewind(stdin);
	system("cls");
	*pY = 5;
	viewPlayer(pPlayer, pX, pY);
	gotoxy(*pX, *pY);
	printf("どの部屋に行ってもらいますか？＞");
	scanf("%d", &dataNum);//外部ファイルからロードした兵士データを格納する先の指定
	*pY = *pY + 1;
	dataNum--;
	loadNum--;
	//ロードする外部ファイルの選択//
	if (loadNum >= 0 && loadNum <= 3)
	{
		if (dataNum == 0)
		{
			pPlayer[dataNum] = playerData[loadNum];
		}
		else if (dataNum == 1)
		{
			pPlayer[dataNum] = playerData[loadNum];
		}
		else if (dataNum == 2)
		{
			pPlayer[dataNum] = playerData[loadNum];
		}
		else if (dataNum == 3)
		{
			pPlayer[dataNum] = playerData[loadNum];
		}
		gotoxy(*pX, *pY);
		printf("ロード成功しました▽");
	}
	else
	{
		gotoxy(*pX, *pY);
		printf("ロードできませんでした▽");
	}
}
//=============================
// 探索
//=============================
void explorePlayer(STATUS* pPlayer, STATUS* pEnemy, STATUS* pBoss, int* pX, int* pY, int* pSizeX, int* pSizeY,bool* pCut)
{
	SKILL_STUCK skill[MAX_RETENTION_SKILL] = {};
	ITEM_STUCK item = {};
	int exSel = 0, check = 0, escape = 0, defeat = 0, stair = 1, bossCount = 0;
	int skillCount[MAX_SKILL] = {};
	while (1)
	{
		*pX = 15, * pY = 5;
		viewPlayer(pPlayer, pX, pY);
		gotoxy(*pX, *pY);
		printf("探索に向かう兵士を選択してください(モード選択画面に戻るには0を入力してください)\n");
		*pY = wherey();
		gotoxy(*pX, *pY);
		printf("＞");
		scanf("%d", &exSel);
		exSel--;
		*pY = *pY + 1;
		//探索するプレイヤーステータスデータの選択//
		if (exSel < 0 || exSel>3)
		{
			*pCut = true;
			rewind(stdin);
			system("cls");
			break;
		}
		else
		{
			if ((pPlayer + exSel)->NAME[0] != '\0')
			{
				textcolor(LIGHTCYAN);
				gotoxy(*pX, *pY);
				printf("【%s:lv%d】:%s\n", pPlayer[exSel].NAME, pPlayer[exSel].LEVEL, pPlayer[exSel].JOB);
				*pY = wherey();
				gotoxy(*pX, *pY);
				printf("【体力:%d　攻撃力%d　防御力%d　魔力%d　魔防%d　素早さ%d　運%d】\n",pPlayer[exSel].LIFE, pPlayer[exSel].ATK, pPlayer[exSel].DEF, pPlayer[exSel].MATK, pPlayer[exSel].MDEF, pPlayer[exSel].SPD, pPlayer[exSel].LUCK);
				*pY = wherey();
				textcolor(WHITE);
				gotoxy(*pX, *pY);
				printf("本当にこの兵士で大丈夫ですか？(はい:1/いいえ:2)＞");
				scanf("%d", &check);
				//プレイヤーステータスデータ誤選択//
				if (check == 1)
				{
					break;
				}
				else
				{
					exSel = 0, check = 0;
					rewind(stdin);
					system("cls");
				}
			}
			else
			{
				gotoxy(*pX, *pY);
				printf("その兵士は選択できません");
				clear();
			}
		}
	}
	rewind(stdin);
	system("cls");
	*pSizeX = 160, *pSizeY = 35;
	controlSize(*pSizeX, *pSizeY);
	if (exSel >= 0 && exSel <= 3)
	{
		*pX = 15, * pY = 5;
		gotoxy(*pX, *pY);
		printf("いざダンジョンへ！！\n\n\n");
		*pY = wherey();
		gotoxy(*pX, *pY);
		printf("第%d階層目▽",stair);
		clear();
		controlSize(*pSizeX, *pSizeY);
		while (1)
		{
			rewind(stdin);
			system("cls");
			srand((unsigned int)time(NULL));
			createEnemy(pEnemy, pPlayer, &exSel);
			//探索イベントのランダム決定//
			if (rand() % 5 == 0 || rand() % 5 == 1)	//エネミーとバトル
			{
				battle(pPlayer, pEnemy, skill, &item, skillCount, &exSel, &defeat, pX, pY);
				if (defeat >= 1)
				{
					gotoxy(*pX, *pY);
					printf("これ以上は探索できそうにない...▽");
					rewind(stdin);
					getchar();
					break;
				}
				else
				{
					*pY = *pY + 1;
					dungeonEscape(&escape, &stair, pX, pY);
					if (escape != 1)
					{
						break;
					}
					rewind(stdin);
					system("cls");
				}
			}
			else if (rand() % 5 == 2 || rand() % 5 == 3)//装備品
			{
				object(&item, pPlayer, &exSel, pX, pY);
				*pY = *pY + 1;
				dungeonEscape(&escape, &stair, pX, pY);
				if (escape != 1)
				{
					break;
				}
				rewind(stdin);
				system("cls");
			}
			else if (rand() % 5 == 4)//階層上昇とボス
			{
				*pY = 5;
				gotoxy(*pX, *pY);
				printf("階段を発見した上りますか?(はい:1/いいえ:2)＞");
				scanf("%d", &check);
				*pY = *pY + 1;
				rewind(stdin);
				system("cls");
				if (check == 1)
				{
					stair = stair + 1;
					if (stair == 10)
					{
						bossCount = αNum;
						createBoss(pBoss, pPlayer, pEnemy, &exSel);
						pEnemy = (pBoss + bossCount);
						battle(pPlayer, pEnemy, skill, &item, skillCount, &exSel, &defeat, pX, pY);
					}
					else if (stair == 20)
					{
						bossCount = βNum;
						createBoss(pBoss, pPlayer, pEnemy, &exSel);
						pEnemy = (pBoss + bossCount);
						battle(pPlayer, pEnemy, skill, &item, skillCount, &exSel, &defeat, pX, pY);
					}
					else if (stair == 30)
					{
						bossCount = εNum;
						createBoss(pBoss, pPlayer, pEnemy, &exSel);
						pEnemy = (pBoss + bossCount);
						battle(pPlayer, pEnemy, skill, &item, skillCount, &exSel, &defeat, pX, pY);
					}
					else if (stair == 50)
					{
						bossCount = ΩNum;
						createBoss(pBoss, pPlayer, pEnemy, &exSel);
						pEnemy = (pBoss + bossCount);
						battle(pPlayer, pEnemy, skill, &item, skillCount, &exSel, &defeat, pX, pY);
					}
					if (defeat >= 1)
					{
						gotoxy(*pX, *pY);
						printf("これ以上は探索できそうにない...▽");
						clear();
						break;
					}
					else
					{
						*pY = *pY + 1;
						dungeonEscape(&escape, &stair, pX, pY);
						if (escape != 1)
						{
							break;
						}
						rewind(stdin);
						system("cls");
					}
					bossCount = 0;
				}
				else
				{
					*pY = *pY + 1;
					dungeonEscape(&escape, &stair, pX, pY);//探索を続けるか、続けないか
					if (escape != 1)
					{
						break;
					}
				}
			}
		}
	}
}
//=============================
// バトル
//=============================
void battle(STATUS* pPlayer, STATUS* pEnemy, SKILL_STUCK* pSkill, ITEM_STUCK* pItem, int* pSkillCount, int* pExSel, int* pDefeat, int* pX, int* pY)
{
	STATUS attacker = {}, defender = {}, chaser = {};//攻守入れ替え用
	SKILL_STUCK enemySkill = {};
	int preemptive = 0, playerMaxLife = 0, enemyMaxLife = 0;
	int damage = 0, critFrag = 0, maxLife = 0, select = 0, skillSel = 0, run = 0, dice = 0, phyFrag = 0, magFrag = 0, phyEnemyFrag = 0, magEnemyFrag = 0, luckLimit = 0, defLimit = 0, enemyLuckLimit = 0, enemyDefLimit = 0, buff = 0;
	int tempoY = 0, tempoX = 0;
	preemptive = pPlayer[*pExSel].SPD;
	maxLife = (pPlayer->LIFE + pItem->ITEM_LIFE);
	enemyMaxLife = pEnemy->LIFE;
	if (preemptive >= pEnemy->SPD)
	{
		attacker = *(pPlayer + *pExSel);
		attacker.LIFE += pItem->ITEM_LIFE;
		attacker.ATK += pItem->ITEM_ATK;
		attacker.DEF += pItem->ITEM_DEF;
		attacker.MATK += pItem->ITEM_MATK;
		attacker.MDEF += pItem->ITEM_MDEF;
		attacker.SPD += pItem->ITEM_SPD;
		attacker.LUCK += pItem->ITEM_LUCK;
		defender = *pEnemy;
	}
	else
	{
		attacker = *pEnemy;
		defender = *(pPlayer + *pExSel);
		defender.LIFE += pItem->ITEM_LIFE;
		defender.ATK += pItem->ITEM_ATK;
		defender.DEF += pItem->ITEM_DEF;
		defender.MATK += pItem->ITEM_MATK;
		defender.MDEF += pItem->ITEM_MDEF;
		defender.SPD += pItem->ITEM_SPD;
		defender.LUCK += pItem->ITEM_LUCK;
	}
	*pX = 15, * pY = 5;
	if (attacker.SPD > defender.SPD)
	{
		gotoxy(*pX, *pY);
		printf("%sがあらわれた！\n\n", pEnemy->NAME);
		*pY = wherey();
	}
	else
	{
		gotoxy(*pX, *pY);
		printf("%sが背後から襲いかかってきた！\n\n", pEnemy->NAME);
		*pY = wherey();
	}
	gotoxy(*pX, *pY);
	printf("~~~~~~~~~~~~~~~~~\n\n");
	*pY = wherey();
	*pX = 18;
	gotoxy(*pX, *pY);
	printf("戦闘開始！\n\n\n");
	*pX = 15;
	*pY = wherey();
	gotoxy(*pX, *pY);
	printf("~~~~~~~~~~~~~~~~~\n\n");
	*pY = wherey();
	gotoxy(*pX,*pY);
	printf("%sの先制攻撃！\n",attacker.NAME);
	*pY = wherey();
	if (attacker.ATK > attacker.MATK)//攻撃力と魔力を比べて、より高い方で先制攻撃のダメージ計算にいれる
	{
		damage = (attacker.ATK - (defender.DEF / (rand() % 2 + 2)));
	}
	else
	{
		damage = (attacker.MATK - (defender.MDEF / (rand() % 2 + 2)));
	}
	if (damage < 0)//ダメージが0以下のときダメージを1にする
	{
		damage = 1;
	}
	maxLife = defender.LIFE;
	defender.LIFE -= damage;
	if (defender.LIFE < 0)//体力を0以下にしない
	{
		defender.LIFE = 0;
	}
	tempoX = *pX, tempoY = *pY;
	*pX = 65, * pY = 5;
	battleView(&attacker, &defender, pX, pY, &playerMaxLife, &enemyMaxLife);
	*pX = tempoX, * pY = tempoY;
	gotoxy(*pX, *pY);
	printf("%sに%dのダメージ\n", defender.NAME, damage);
	*pY = wherey();
	gotoxy(*pX, *pY);
	printf("【%体力%d → 体力%d】▽", maxLife, defender.LIFE);
	*pY = wherey(), *pX = wherex();
	gotoxy(*pX, *pY);
	if (defender.LIFE > 0)//先制攻撃で体力が0以上でバトル開始
	{
		clear();
		for (int i=1;;i++)
		{
			*pX = 15, * pY = 5;
			chaser = attacker;
			attacker = defender;
			defender = chaser;
			// 現在のプレイヤー、エネミーのステータスの表示 //
			*pX = 65, * pY = 5;
			battleView(&attacker, &defender, pX, pY, &playerMaxLife, &enemyMaxLife);
			*pX = 15, * pY = 5;
			if (attacker.IDEN == playerIdenNum)//プレイヤーがアタッカーになったとき
			{
				*pX = 15, * pY = 5;
				gotoxy(*pX, *pY);
				printf("『攻撃:1 魔法:2 スキル:3 逃げる:4』　＞");
				scanf("%d", &select);//行動選択
				*pY = *pY + 2;
				if (select == 1)//攻撃力と防御力を参照しダメージ計算
				{
					gotoxy(*pX, *pY);
					printf("%sの攻撃！\n\n", attacker.NAME);
					*pY = wherey();
					if (rand() % (attacker.LUCK / 2) > rand() % 100)//クリティカル
					{
						if (defender.ATTRIBUTE_NUM == fire)
						{
							if (attacker.ATTRIBUTE_NUM == fire)
							{
								damage = attacker.ATK*1.2f-(defender.DEF/(rand()%3+1));
							}
							else if (attacker.ATTRIBUTE_NUM == thunder)
							{
								damage = (attacker.ATK * 1.2f - (defender.DEF / (rand() % 3 + 2))) * 1.2f;
							}
							else if (attacker.ATTRIBUTE_NUM == soil)
							{
								damage = (attacker.ATK * 1.2f - (defender.DEF / (rand() % 3 + 2))) * 0.8f;
							}
							else if (attacker.ATTRIBUTE_NUM == normal)
							{
								damage = attacker.ATK * 1.2f - (defender.DEF / (rand() % 3 + 2));
							}
						}
						else if (defender.ATTRIBUTE_NUM == thunder)
						{
							if (attacker.ATTRIBUTE_NUM == fire)
							{
								damage = (attacker.ATK * 1.2f - (defender.DEF / (rand() % 3 + 2))) * 0.8f;
							}
							else if (attacker.ATTRIBUTE_NUM == thunder)
							{
								damage = attacker.ATK * 1.2f - (defender.DEF / (rand() % 3 + 2));
							}
							else if (attacker.ATTRIBUTE_NUM == soil)
							{
								damage = (attacker.ATK * 1.2f - (defender.DEF / (rand() % 3 + 2))) * 1.2f;
							}
							else if (attacker.ATTRIBUTE_NUM == normal)
							{
								damage = attacker.ATK * 1.2f - (defender.DEF / (rand() % 3 + 2));
							}
						}
						else if (defender.ATTRIBUTE_NUM == soil)
						{
							if (attacker.ATTRIBUTE_NUM == fire)
							{
								damage = (attacker.ATK * 1.2f - (defender.DEF / (rand() % 3 + 2))) * 1.2f;
							}
							else if (attacker.ATTRIBUTE_NUM == thunder)
							{
								damage = (attacker.ATK * 1.2f - (defender.DEF / (rand() % 3 + 2))) * 0.8f;
							}
							else if (attacker.ATTRIBUTE_NUM == soil)
							{
								damage = attacker.ATK * 1.2f - (defender.DEF / (rand() % 3 + 2));
							}
							else if (attacker.ATTRIBUTE_NUM == normal)
							{
								damage = attacker.ATK * 1.2f - (defender.DEF / (rand() % 3 + 2));
							}
						}
						else if (defender.ATTRIBUTE_NUM == normal)
						{
							if (attacker.ATTRIBUTE_NUM == fire)
							{
								damage = attacker.ATK * 1.2f - (defender.DEF / (rand() % 3 + 2));
							}
							else if (attacker.ATTRIBUTE_NUM == thunder)
							{
								damage = attacker.ATK * 1.2f - (defender.DEF / (rand() % 3 + 2));
							}
							else if (attacker.ATTRIBUTE_NUM == soil)
							{
								damage = attacker.ATK * 1.2f - (defender.DEF / (rand() % 3 + 2));
							}
							else if (attacker.ATTRIBUTE_NUM == normal)
							{
								damage = attacker.ATK * 1.2f - (defender.DEF / (rand() % 3 + 2));
							}
						}
						critFrag = 1;
					}
					else//notクリティカル
					{
						if (defender.ATTRIBUTE_NUM == fire)
						{
							if (attacker.ATTRIBUTE_NUM == fire)
							{
								damage = attacker.ATK - (defender.DEF / (rand() % 2 + 2));
							}
							else if (attacker.ATTRIBUTE_NUM == thunder)
							{
								damage = (attacker.ATK - (defender.DEF / (rand() % 2 + 2))) * 1.2f;
							}
							else if (attacker.ATTRIBUTE_NUM == soil)
							{
								damage = (attacker.ATK - (defender.DEF / (rand() % 2 + 2))) * 0.8f;
							}
							else if (attacker.ATTRIBUTE_NUM == normal)
							{
								damage = attacker.ATK - (defender.DEF / (rand() % 2 + 2));
							}
						}
						else if (defender.ATTRIBUTE_NUM == thunder)
						{
							if (attacker.ATTRIBUTE_NUM == fire)
							{
								damage = (attacker.ATK - (defender.DEF / (rand() % 2 + 2))) * 0.8f;
							}
							else if (attacker.ATTRIBUTE_NUM == thunder)
							{
								damage = attacker.ATK - (defender.DEF / (rand() % 2 + 2));
							}
							else if (attacker.ATTRIBUTE_NUM == soil)
							{
								damage = (attacker.ATK - (defender.DEF / (rand() % 2 + 2))) * 1.2f;
							}
							else if (attacker.ATTRIBUTE_NUM == normal)
							{
								damage = attacker.ATK - (defender.DEF / (rand() % 2 + 2));
							}
						}
						else if (defender.ATTRIBUTE_NUM == soil)
						{
							if (attacker.ATTRIBUTE_NUM == fire)
							{
								damage = (attacker.ATK - (defender.DEF / (rand() % 2 + 2))) * 1.2f;
							}
							else if (attacker.ATTRIBUTE_NUM == thunder)
							{
								damage = (attacker.ATK - (defender.DEF / (rand() % 2 + 2))) * 0.8f;
							}
							else if (attacker.ATTRIBUTE_NUM == soil)
							{
								damage = attacker.ATK - (defender.DEF / (rand() % 2 + 2));
							}
							else if (attacker.ATTRIBUTE_NUM == normal)
							{
								damage = attacker.ATK - (defender.DEF / (rand() % 2 + 2));
							}
						}
						else if (defender.ATTRIBUTE_NUM == normal)
						{
							if (attacker.ATTRIBUTE_NUM == fire)
							{
								damage = attacker.ATK - (defender.DEF / (rand() % 2 + 2));
							}
							else if (attacker.ATTRIBUTE_NUM == thunder)
							{
								damage = attacker.ATK - (defender.DEF / (rand() % 2 + 2));
							}
							else if (attacker.ATTRIBUTE_NUM == soil)
							{
								damage = attacker.ATK - (defender.DEF / (rand() % 2 + 2));
							}
							else if (attacker.ATTRIBUTE_NUM == normal)
							{
								damage = attacker.ATK - (defender.DEF / (rand() % 2 + 2));
							}
						}
						critFrag = 0;
						if (damage < 0)//ダメージが0以下のときダメージを1にする
						{
							damage = 1;
						}
					}
					if (phyFrag == 1)//スキル効果の終了
					{
						attacker.ATK -= attacker.ATK / 2;
						phyFrag = 0;
					}
					if (critFrag > 0)
					{
						gotoxy(*pX, *pY);
						printf("クリティカル！\n");
						*pY = wherey();
					}
					gotoxy(*pX, *pY);
					printf("%sに%dのダメージ\n", defender.NAME, damage);
					*pY = wherey();
					maxLife = defender.LIFE;
					defender.LIFE -= damage;
					if (defender.LIFE < 0) //体力を0以下にしない
					{
						defender.LIFE = 0;
					}
					gotoxy(*pX, *pY);
					printf("【体力%d → 体力%d】▽", maxLife, defender.LIFE);
					*pY = wherey(), * pX = wherex();
				}
				else if (select == 2)//魔力と魔防を参照しダメージ計算
				{
					gotoxy(*pX, *pY);
					printf("%sの魔法！\n\n", attacker.NAME);
					*pY = wherey();
					if (rand() % (attacker.LUCK / 2) > rand() % 100)//クリティカル
					{
						if (defender.ATTRIBUTE_NUM == fire)
						{
							if (attacker.ATTRIBUTE_NUM == fire)
							{
								damage = attacker.MATK * 1.2f - (defender.MDEF / (rand() % 3 + 2));
							}
							else if (attacker.ATTRIBUTE_NUM == thunder)
							{
								damage = (attacker.MATK * 1.2f - (defender.MDEF / (rand() % 3 + 2))) * 1.2f;
							}
							else if (attacker.ATTRIBUTE_NUM == soil)
							{
								damage = (attacker.MATK * 1.2f - (defender.MDEF / (rand() % 3 + 2))) * 0.8f;
							}
							else if (attacker.ATTRIBUTE_NUM == normal)
							{
								damage = attacker.MATK * 1.2f - (defender.MDEF / (rand() % 3 + 2));
							}
						}
						else if (defender.ATTRIBUTE_NUM == thunder)
						{
							if (attacker.ATTRIBUTE_NUM == fire)
							{
								damage = (attacker.MATK * 1.2f - (defender.MDEF / (rand() % 3 + 2))) * 0.8f;
							}
							else if (attacker.ATTRIBUTE_NUM == thunder)
							{
								damage = attacker.MATK * 1.2f - (defender.MDEF / (rand() % 3 + 2));
							}
							else if (attacker.ATTRIBUTE_NUM == soil)
							{
								damage = (attacker.MATK * 1.2f - (defender.MDEF / (rand() % 3 + 2))) * 1.2f;
							}
							else if (attacker.ATTRIBUTE_NUM == normal)
							{
								damage = attacker.MATK * 1.2f - (defender.MDEF / (rand() % 3 + 2));
							}
						}
						else if (defender.ATTRIBUTE_NUM == soil)
						{
							if (attacker.ATTRIBUTE_NUM == fire)
							{
								damage = (attacker.MATK * 1.2f - (defender.MDEF / (rand() % 3 + 2))) * 1.2f;
							}
							else if (attacker.ATTRIBUTE_NUM == thunder)
							{
								damage = (attacker.MATK * 1.2f - (defender.MDEF / (rand() % 3 + 2))) * 0.8f;
							}
							else if (attacker.ATTRIBUTE_NUM == soil)
							{
								damage = attacker.MATK * 1.2f - (defender.MDEF / (rand() % 3 + 2));
							}
							else if (attacker.ATTRIBUTE_NUM == normal)
							{
								damage = attacker.MATK * 1.2f - (defender.MDEF / (rand() % 3 + 2));
							}
						}
						else if (defender.ATTRIBUTE_NUM == normal)
						{
							if (attacker.ATTRIBUTE_NUM == fire)
							{
								damage = attacker.MATK * 1.2f - (defender.MDEF / (rand() % 3 + 2));
							}
							else if (attacker.ATTRIBUTE_NUM == thunder)
							{
								damage = attacker.MATK * 1.2f - (defender.MDEF / (rand() % 3 + 2));
							}
							else if (attacker.ATTRIBUTE_NUM == soil)
							{
								damage = attacker.MATK * 1.2f - (defender.MDEF / (rand() % 3 + 2));
							}
							else if (attacker.ATTRIBUTE_NUM == normal)
							{
								damage = attacker.MATK * 1.2f - (defender.MDEF / (rand() % 3 + 2));
							}
						}
						critFrag = 1;
					}
					else//notクリティカル
					{
						if (defender.ATTRIBUTE_NUM == fire)
						{
							if (attacker.ATTRIBUTE_NUM == fire)
							{
								damage = attacker.MATK - (defender.MDEF / (rand() % 2 + 2));
							}
							else if (attacker.ATTRIBUTE_NUM == thunder)
							{
								damage = (attacker.MATK - (defender.MDEF / (rand() % 2 + 2))) * 1.2f;
							}
							else if (attacker.ATTRIBUTE_NUM == soil)
							{
								damage = (attacker.MATK - (defender.MDEF / (rand() % 2 + 2))) * 0.8f;
							}
							else if (attacker.ATTRIBUTE_NUM == normal)
							{
								damage = attacker.MATK - (defender.MDEF / (rand() % 2 + 2));
							}
						}
						else if (defender.ATTRIBUTE_NUM == thunder)
						{
							if (attacker.ATTRIBUTE_NUM == fire)
							{
								damage = (attacker.MATK - (defender.MDEF / (rand() % 2 + 2))) * 0.8f;
							}
							else if (attacker.ATTRIBUTE_NUM == thunder)
							{
								damage = attacker.MATK - (defender.MDEF / (rand() % 2 + 2));
							}
							else if (attacker.ATTRIBUTE_NUM == soil)
							{
								damage = (attacker.MATK - (defender.MDEF / (rand() % 2 + 2))) * 1.2f;
							}
							else if (attacker.ATTRIBUTE_NUM == normal)
							{
								damage = attacker.MATK - (defender.MDEF / (rand() % 2 + 2));
							}
						}
						else if (defender.ATTRIBUTE_NUM == soil)
						{
							if (attacker.ATTRIBUTE_NUM == fire)
							{
								damage = (attacker.MATK - (defender.MDEF / (rand() % 2 + 2))) * 1.2f;
							}
							else if (attacker.ATTRIBUTE_NUM == thunder)
							{
								damage = (attacker.MATK - (defender.MDEF / (rand() % 2 + 2))) * 0.8f;
							}
							else if (attacker.ATTRIBUTE_NUM == soil)
							{
								damage = attacker.MATK - (defender.MDEF / (rand() % 2 + 2));
							}
							else if (attacker.ATTRIBUTE_NUM == normal)
							{
								damage = attacker.MATK - (defender.MDEF / (rand() % 2 + 2));
							}
						}
						else if (defender.ATTRIBUTE_NUM == normal)
						{
							if (attacker.ATTRIBUTE_NUM == fire)
							{
								damage = attacker.MATK - (defender.MDEF / (rand() % 2 + 2));
							}
							else if (attacker.ATTRIBUTE_NUM == thunder)
							{
								damage = attacker.MATK - (defender.MDEF / (rand() % 2 + 2));
							}
							else if (attacker.ATTRIBUTE_NUM == soil)
							{
								damage = attacker.MATK - (defender.MDEF / (rand() % 2 + 2));
							}
							else if (attacker.ATTRIBUTE_NUM == normal)
							{
								damage = attacker.MATK - (defender.MDEF / (rand() % 2 + 2));
							}
						}
						critFrag = 0;
						if (damage < 0)//ダメージが0以下のときダメージを1にする
						{
							damage = 1;
						}
					}
					if (magFrag == 1) //スキル効果の終了
					{
						attacker.MATK -= attacker.MATK / 2;
						magFrag = 0;
					}
					if (critFrag > 0)
					{
						gotoxy(*pX, *pY);
						printf("クリティカル！\n");
						*pY = wherey();
					}
					gotoxy(*pX, *pY);
					printf("%sに%dのダメージ\n", defender.NAME, damage);
					*pY = wherey();
					maxLife = defender.LIFE;
					defender.LIFE -= damage;
					if (defender.LIFE < 0)//体力を0以下にしない
					{
						defender.LIFE = 0;
					}
					gotoxy(*pX, *pY);
					printf("【体力%d → 体力%d】▽", maxLife, defender.LIFE);
					*pY = wherey(), * pX = wherex();
				}
				else if (select == 3)//スキルを参照しダメージ計算
				{
					action(&attacker, pSkill, &defender, &damage, &phyFrag, &magFrag, &luckLimit, &defLimit, &buff, pX, pY, &critFrag, &playerMaxLife, &enemyMaxLife, &skillSel);
					*pX = 15, *pY = 15;
					if (buff == 0)
					{
						if (damage < 0)
						{
							damage = 1;
						}
						gotoxy(*pX, *pY);
						printf("スキル:%s\n", (pSkill + skillSel)->SKILL_NAME);
						*pY = wherey();
						if (critFrag > 0)
						{
							gotoxy(*pX, *pY);
							printf("クリティカル！\n");
							*pY = wherey();
						}
						gotoxy(*pX, *pY);
						printf("%sに%dのダメージ\n", defender.NAME, damage);
						*pY = wherey();
						maxLife = defender.LIFE;
						defender.LIFE -= damage;
						if (defender.LIFE < 0)
						{
							defender.LIFE = 0;
						}
						gotoxy(*pX, *pY);
						printf("【体力%d → 体力%d】▽", maxLife, defender.LIFE);
						*pY = wherey(),*pX=wherex();
						if (phyFrag == 1 || magFrag == 1)
						{
							phyFrag = 0;
							magFrag = 0;
						}
					}
					else//バフ系スキル、行動をしない場合の処理
					{
						buff = 0;
					}
				}
				else if (select == 4)
				{
					if (defender.IDEN == enemyIdenNum)
					{
						gotoxy(*pX, *pY);
						printf("%sは逃走を試みた\n\n", attacker.NAME);
						*pY = wherey();
						run = (attacker.SPD / 5) * (attacker.LUCK / 3);
						if ((rand() % run) < run / 3)
						{
							gotoxy(*pX, *pY);
							printf("%sは逃走に成功した！", attacker.NAME);
							break;
						}
						else
						{
							gotoxy(*pX, *pY);
							printf("回り込まれた！▽");
							*pY = wherey(), * pX = wherex();
						}
					}
					else if (defender.IDEN == bossIdenNum)
					{
						gotoxy(*pX, *pY);
						printf("逃げられない！▽");
						*pY = wherey(), * pX = wherex();
					}
				}
				else
				{
					gotoxy(*pX, *pY);
					printf("なにもしない");
					*pY = wherey(), * pX = wherex();
				}
			}
			else
			{
				//現在のプレイヤー、エネミーのステータスの表示
				*pX = 65, * pY = 5;
				battleView(&attacker, &defender, pX, pY, &playerMaxLife, &enemyMaxLife);
				*pX = 15, * pY = 5;
				dice = rand() % 100;
				if (dice >= 0 && dice <= 34)
				{
					gotoxy(*pX, *pY);
					printf("%sの攻撃！\n\n", attacker.NAME);
					*pY = wherey();
					if (rand() % (attacker.LUCK / 2) > rand() % 100)//クリティカル
					{
						if (defender.ATTRIBUTE_NUM == fire)
						{
							if (attacker.ATTRIBUTE_NUM == fire)
							{
								damage = attacker.ATK * 1.2f - (defender.DEF / (rand() % 3 + 1));
							}
							else if (attacker.ATTRIBUTE_NUM == thunder)
							{
								damage = (attacker.ATK * 1.2f - (defender.DEF / (rand() % 3 + 2))) * 1.2f;
							}
							else if (attacker.ATTRIBUTE_NUM == soil)
							{
								damage = (attacker.ATK * 1.2f - (defender.DEF / (rand() % 3 + 2))) * 0.8f;
							}
							else if (attacker.ATTRIBUTE_NUM == normal)
							{
								damage = attacker.ATK * 1.2f - (defender.DEF / (rand() % 3 + 2));
							}
						}
						else if (defender.ATTRIBUTE_NUM == thunder)
						{
							if (attacker.ATTRIBUTE_NUM == fire)
							{
								damage = (attacker.ATK * 1.2f - (defender.DEF / (rand() % 3 + 2))) * 0.8f;
							}
							else if (attacker.ATTRIBUTE_NUM == thunder)
							{
								damage = attacker.ATK * 1.2f - (defender.DEF / (rand() % 3 + 2));
							}
							else if (attacker.ATTRIBUTE_NUM == soil)
							{
								damage = (attacker.ATK * 1.2f - (defender.DEF / (rand() % 3 + 2))) * 1.2f;
							}
							else if (attacker.ATTRIBUTE_NUM == normal)
							{
								damage = attacker.ATK * 1.2f - (defender.DEF / (rand() % 3 + 2));
							}
						}
						else if (defender.ATTRIBUTE_NUM == soil)
						{
							if (attacker.ATTRIBUTE_NUM == fire)
							{
								damage = (attacker.ATK * 1.2f - (defender.DEF / (rand() % 3 + 2))) * 1.2f;
							}
							else if (attacker.ATTRIBUTE_NUM == thunder)
							{
								damage = (attacker.ATK * 1.2f - (defender.DEF / (rand() % 3 + 2))) * 0.8f;
							}
							else if (attacker.ATTRIBUTE_NUM == soil)
							{
								damage = attacker.ATK * 1.2f - (defender.DEF / (rand() % 3 + 2));
							}
							else if (attacker.ATTRIBUTE_NUM == normal)
							{
								damage = attacker.ATK * 1.2f - (defender.DEF / (rand() % 3 + 2));
							}
						}
						else if (defender.ATTRIBUTE_NUM == normal)
						{
							if (attacker.ATTRIBUTE_NUM == fire)
							{
								damage = attacker.ATK * 1.2f - (defender.DEF / (rand() % 3 + 2));
							}
							else if (attacker.ATTRIBUTE_NUM == thunder)
							{
								damage = attacker.ATK * 1.2f - (defender.DEF / (rand() % 3 + 2));
							}
							else if (attacker.ATTRIBUTE_NUM == soil)
							{
								damage = attacker.ATK * 1.2f - (defender.DEF / (rand() % 3 + 2));
							}
							else if (attacker.ATTRIBUTE_NUM == normal)
							{
								damage = attacker.ATK * 1.2f - (defender.DEF / (rand() % 3 + 2));
							}
						}
						critFrag = 1;
					} 
					else//notクリティカル
					{
						if (defender.ATTRIBUTE_NUM == fire)
						{
							if (attacker.ATTRIBUTE_NUM == fire)
							{
								damage = attacker.ATK - (defender.DEF / (rand() % 2 + 2));
							}
							else if (attacker.ATTRIBUTE_NUM == thunder)
							{
								damage = (attacker.ATK - (defender.DEF / (rand() % 2 + 2))) * 1.2f;
							}
							else if (attacker.ATTRIBUTE_NUM == soil)
							{
								damage = (attacker.ATK - (defender.DEF / (rand() % 2 + 2))) * 0.8f;
							}
							else if (attacker.ATTRIBUTE_NUM == normal)
							{
								damage = attacker.ATK - (defender.DEF / (rand() % 2 + 2));
							}
						}
						else if (defender.ATTRIBUTE_NUM == thunder)
						{
							if (attacker.ATTRIBUTE_NUM == fire)
							{
								damage = (attacker.ATK - (defender.DEF / (rand() % 2 + 2))) * 0.8f;
							}
							else if (attacker.ATTRIBUTE_NUM == thunder)
							{
								damage = attacker.ATK - (defender.DEF / (rand() % 2 + 2));
							}
							else if (attacker.ATTRIBUTE_NUM == soil)
							{
								damage = (attacker.ATK - (defender.DEF / (rand() % 2 + 2))) * 1.2f;
							}
							else if (attacker.ATTRIBUTE_NUM == normal)
							{
								damage = attacker.ATK - (defender.DEF / (rand() % 2 + 2));
							}
						}
						else if (defender.ATTRIBUTE_NUM == soil)
						{
							if (attacker.ATTRIBUTE_NUM == fire)
							{
								damage = (attacker.ATK - (defender.DEF / (rand() % 2 + 2))) * 1.2f;
							}
							else if (attacker.ATTRIBUTE_NUM == thunder)
							{
								damage = (attacker.ATK - (defender.DEF / (rand() % 2 + 2))) * 0.8f;
							}
							else if (attacker.ATTRIBUTE_NUM == soil)
							{
								damage = attacker.ATK - (defender.DEF / (rand() % 2 + 2));
							}
							else if (attacker.ATTRIBUTE_NUM == normal)
							{
								damage = attacker.ATK - (defender.DEF / (rand() % 2 + 2));
							}
						}
						else if (defender.ATTRIBUTE_NUM == normal)
						{
							if (attacker.ATTRIBUTE_NUM == fire)
							{
								damage = attacker.ATK - (defender.DEF / (rand() % 2 + 2));
							}
							else if (attacker.ATTRIBUTE_NUM == thunder)
							{
								damage = attacker.ATK - (defender.DEF / (rand() % 2 + 2));
							}
							else if (attacker.ATTRIBUTE_NUM == soil)
							{
								damage = attacker.ATK - (defender.DEF / (rand() % 2 + 2));
							}
							else if (attacker.ATTRIBUTE_NUM == normal)
							{
								damage = attacker.ATK - (defender.DEF / (rand() % 2 + 2));
							}
						}
						critFrag = 0;
						if (damage < 0)
						{
							damage = 1;
						}
					}
					if (phyEnemyFrag == 1)
					{
						attacker.ATK -= attacker.ATK / 2;
						phyEnemyFrag = 0;
					}
					if (critFrag > 0)
					{
						gotoxy(*pX, *pY);
						printf("クリティカル！\n");
						*pY = wherey();
					}
					gotoxy(*pX, *pY);
					printf("%sに%dのダメージ\n", defender.NAME, damage);
					*pY = wherey();
					maxLife = defender.LIFE;
					defender.LIFE -= damage;
					if (defender.LIFE < 0)
					{
						defender.LIFE = 0;
					}
					gotoxy(*pX, *pY);
					printf("【体力%d → 体力%d】▽", maxLife, defender.LIFE);
					*pY = wherey(), * pX = wherex();
				}
				else if (dice >= 35 && dice <= 69)
				{
					gotoxy(*pX, *pY);
					printf("%sの魔法！\n\n", attacker.NAME);
					*pY = wherey();
					if (rand() % (attacker.LUCK / 2) > rand() % 100)//クリティカル
					{
						if (defender.ATTRIBUTE_NUM == fire)
						{
							if (attacker.ATTRIBUTE_NUM == fire)
							{
								damage = attacker.MATK * 1.2f - (defender.MDEF / (rand() % 3 + 2));
							}
							else if (attacker.ATTRIBUTE_NUM == thunder)
							{
								damage = (attacker.MATK * 1.2f - (defender.MDEF / (rand() % 3 + 2))) * 1.2f;
							}
							else if (attacker.ATTRIBUTE_NUM == soil)
							{
								damage = (attacker.MATK * 1.2f - (defender.MDEF / (rand() % 3 + 2))) * 0.8f;
							}
							else if (attacker.ATTRIBUTE_NUM == normal)
							{
								damage = attacker.MATK * 1.2f - (defender.MDEF / (rand() % 3 + 2));
							}
						}
						else if (defender.ATTRIBUTE_NUM == thunder)
						{
							if (attacker.ATTRIBUTE_NUM == fire)
							{
								damage = (attacker.MATK * 1.2f - (defender.MDEF / (rand() % 3 + 2))) * 0.8f;
							}
							else if (attacker.ATTRIBUTE_NUM == thunder)
							{
								damage = attacker.MATK * 1.2f - (defender.MDEF / (rand() % 3 + 2));
							}
							else if (attacker.ATTRIBUTE_NUM == soil)
							{
								damage = (attacker.MATK * 1.2f - (defender.MDEF / (rand() % 3 + 2))) * 1.2f;
							}
							else if (attacker.ATTRIBUTE_NUM == normal)
							{
								damage = attacker.MATK * 1.2f - (defender.MDEF / (rand() % 3 + 2));
							}
						}
						else if (defender.ATTRIBUTE_NUM == soil)
						{
							if (attacker.ATTRIBUTE_NUM == fire)
							{
								damage = (attacker.MATK * 1.2f - (defender.MDEF / (rand() % 3 + 2))) * 1.2f;
							}
							else if (attacker.ATTRIBUTE_NUM == thunder)
							{
								damage = (attacker.MATK * 1.2f - (defender.MDEF / (rand() % 3 + 2))) * 0.8f;
							}
							else if (attacker.ATTRIBUTE_NUM == soil)
							{
								damage = attacker.MATK * 1.2f - (defender.MDEF / (rand() % 3 + 2));
							}
							else if (attacker.ATTRIBUTE_NUM == normal)
							{
								damage = attacker.MATK * 1.2f - (defender.MDEF / (rand() % 3 + 2));
							}
						}
						else if (defender.ATTRIBUTE_NUM == normal)
						{
							if (attacker.ATTRIBUTE_NUM == fire)
							{
								damage = attacker.MATK * 1.2f - (defender.MDEF / (rand() % 3 + 2));
							}
							else if (attacker.ATTRIBUTE_NUM == thunder)
							{
								damage = attacker.MATK * 1.2f - (defender.MDEF / (rand() % 3 + 2));
							}
							else if (attacker.ATTRIBUTE_NUM == soil)
							{
								damage = attacker.MATK * 1.2f - (defender.MDEF / (rand() % 3 + 2));
							}
							else if (attacker.ATTRIBUTE_NUM == normal)
							{
								damage = attacker.MATK * 1.2f - (defender.MDEF / (rand() % 3 + 2));
							}
						}
						critFrag = 1;
					}
					else//notクリティカル
					{
						if (defender.ATTRIBUTE_NUM == fire)
						{
							if (attacker.ATTRIBUTE_NUM == fire)
							{
								damage = attacker.MATK - (defender.MDEF / (rand() % 2 + 2));
							}
							else if (attacker.ATTRIBUTE_NUM == thunder)
							{
								damage = (attacker.MATK - (defender.MDEF / (rand() % 2 + 2))) * 1.2f;
							}
							else if (attacker.ATTRIBUTE_NUM == soil)
							{
								damage = (attacker.MATK - (defender.MDEF / (rand() % 2 + 2))) * 0.8f;
							}
							else if (attacker.ATTRIBUTE_NUM == normal)
							{
								damage = attacker.MATK - (defender.MDEF / (rand() % 2 + 2));
							}
						}
						else if (defender.ATTRIBUTE_NUM == thunder)
						{
							if (attacker.ATTRIBUTE_NUM == fire)
							{
								damage = (attacker.MATK - (defender.MDEF / (rand() % 2 + 2))) * 0.8f;
							}
							else if (attacker.ATTRIBUTE_NUM == thunder)
							{
								damage = attacker.MATK - (defender.MDEF / (rand() % 2 + 2));
							}
							else if (attacker.ATTRIBUTE_NUM == soil)
							{
								damage = (attacker.MATK - (defender.MDEF / (rand() % 2 + 2))) * 1.2f;
							}
							else if (attacker.ATTRIBUTE_NUM == normal)
							{
								damage = attacker.MATK - (defender.MDEF / (rand() % 2 + 2));
							}
						}
						else if (defender.ATTRIBUTE_NUM == soil)
						{
							if (attacker.ATTRIBUTE_NUM == fire)
							{
								damage = (attacker.MATK - (defender.MDEF / (rand() % 2 + 2))) * 1.2f;
							}
							else if (attacker.ATTRIBUTE_NUM == thunder)
							{
								damage = (attacker.MATK - (defender.MDEF / (rand() % 2 + 2))) * 0.8f;
							}
							else if (attacker.ATTRIBUTE_NUM == soil)
							{
								damage = attacker.MATK - (defender.MDEF / (rand() % 2 + 2));
							}
							else if (attacker.ATTRIBUTE_NUM == normal)
							{
								damage = attacker.MATK - (defender.MDEF / (rand() % 2 + 2));
							}
						}
						else if (defender.ATTRIBUTE_NUM == normal)
						{
							if (attacker.ATTRIBUTE_NUM == fire)
							{
								damage = attacker.MATK - (defender.MDEF / (rand() % 2 + 2));
							}
							else if (attacker.ATTRIBUTE_NUM == thunder)
							{
								damage = attacker.MATK - (defender.MDEF / (rand() % 2 + 2));
							}
							else if (attacker.ATTRIBUTE_NUM == soil)
							{
								damage = attacker.MATK - (defender.MDEF / (rand() % 2 + 2));
							}
							else if (attacker.ATTRIBUTE_NUM == normal)
							{
								damage = attacker.MATK - (defender.MDEF / (rand() % 2 + 2));
							}
						}
						critFrag = 0;
						if (damage < 0)
						{
							damage = 1;
						}
					}
					if (magEnemyFrag == 1)
					{
						attacker.MATK -= attacker.MATK / 2;
						magEnemyFrag = 0;
					}
					if (critFrag > 0)
					{
						gotoxy(*pX, *pY);
						printf("クリティカル！\n");
						*pY = wherey();
					}
					gotoxy(*pX, *pY);
					printf("%sに%dのダメージ\n", defender.NAME, damage);
					*pY = wherey();
					maxLife = defender.LIFE;
					defender.LIFE -= damage;
					if (defender.LIFE < 0)
					{
						defender.LIFE = 0;
					}
					gotoxy(*pX, *pY);
					printf("【体力%d → 体力%d】▽", maxLife, defender.LIFE);
					*pY = wherey(), * pX = wherex();
				}
				else if (dice >= 70 && dice <= 89)
				{
					rewind(stdin);
					system("cls");
					//現在のプレイヤー、エネミーのステータスの表示
					*pX = 65, * pY = 5;
					battleView(&attacker, &defender, pX, pY, &playerMaxLife, &enemyMaxLife);
					*pX = 15, * pY = 5;
					skillEnemy(&attacker, &defender, &enemySkill, &damage, &buff, &enemyLuckLimit, &enemyDefLimit, &phyEnemyFrag, &magEnemyFrag, pX, pY,&critFrag);
					if (buff == 0)
					{
						if (damage < 0)
						{
							damage = 1;
						}
						gotoxy(*pX, *pY);
						printf("スキル:%s\n", enemySkill.SKILL_NAME);
						*pY = wherey();
						if (critFrag > 0)
						{
							gotoxy(*pX, *pY);
							printf("クリティカル！\n");
							*pY = wherey();
						}
						gotoxy(*pX, *pY);
						printf("%sに%dのダメージ\n", defender.NAME, damage);
						*pY = wherey();
						maxLife = defender.LIFE;
						defender.LIFE -= damage;
						if (defender.LIFE < 0)
						{
							defender.LIFE = 0;
						}
						gotoxy(*pX, *pY);
						printf("【体力%d → 体力%d】▽", maxLife, defender.LIFE);
						*pY = wherey(), * pX = wherex();
						if (phyEnemyFrag == 1 || magEnemyFrag == 1)
						{
							phyEnemyFrag = 0;
							magEnemyFrag = 0;
						}
					}
					else
					{
						buff = 0;
					}
				}
				else
				{
					if (attacker.IDEN == enemyIdenNum)
					{
						gotoxy(*pX, *pY);
						printf("%sは逃走を試みた\n\n", attacker.NAME);
						*pY = wherey();
						run = (attacker.SPD / 5) * (attacker.LUCK / 3);
						if ((rand() % run) < run / 3)
						{
							gotoxy(*pX, *pY);
							printf("%sは逃走に成功した！", attacker.NAME);
							break;
						}
						else
						{
							gotoxy(*pX, *pY);
							printf("逃走を阻止した！▽");
							*pY = wherey(), * pX = wherex();
						}
					}
					else if (attacker.IDEN == bossIdenNum)
					{
						gotoxy(*pX, *pY);
						printf("じっとこっちを見ている▽");
						*pY = wherey(), * pX = wherex();
					}
				}
			}
			if (defender.LIFE <= 0)
			{
				*pY = *pY + 3;
				tempoY = *pY, tempoX = *pX;
				*pX = 65, * pY = 5;
				battleView(&attacker, &defender, pX, pY, &playerMaxLife, &enemyMaxLife);
				*pY = tempoY, *pX = 15;
				gotoxy(*pX, *pY);
				printf("%sは力尽きた...", defender.NAME);
				*pY = (wherey()+1), * pX = 15;
				if (attacker.IDEN == playerIdenNum)
				{
					levelUp(pPlayer, pSkill, pSkillCount, pExSel, pX, pY);
				}
				else if (defender.IDEN == playerIdenNum)
				{
					*pDefeat = 1;
				}
				break;
			}
			tempoY = *pY, tempoX = *pX;
			*pX = 65, * pY = 5;
			battleView(&attacker, &defender, pX, pY, &playerMaxLife, &enemyMaxLife);
			*pY = tempoY;
			*pX = tempoX;
			gotoxy(*pX, *pY);
			clear();
		}
	}
	else
	{
		tempoX = *pX, tempoY = (*pY + 1);
		*pX = 65, * pY = 5;
		battleView(&attacker, &defender, pX, pY, &playerMaxLife, &enemyMaxLife);
		*pY = tempoY, * pX = 15;
		gotoxy(*pX, *pY);
		printf("%sは力尽きた...", defender.NAME);
		*pY = (wherey()+1), * pX = 15;
		if (attacker.IDEN == playerIdenNum)
		{
			levelUp(pPlayer, pSkill, pSkillCount, pExSel, pX, pY);
		}
		else if (defender.IDEN == playerIdenNum)
		{
			*pDefeat = 1;
		}
	}
	deleteEnemy(pEnemy);
}
//=============================
// バトルステータス表示
//=============================
void battleView(STATUS* pAttacker,STATUS* pDefender,int* pX,int* pY,int* pPlayerMaxLife,int* pEnemyMaxLife)
{
	if (pAttacker->LIFE < (*pPlayerMaxLife / 2) || pAttacker->LIFE < (*pEnemyMaxLife / 2))
	{
		textcolor(YELLOW);
	}
	if (pAttacker->LIFE < (*pPlayerMaxLife / 3) || pAttacker->LIFE < (*pEnemyMaxLife / 3))
	{
		textcolor(LIGHTRED);
	}
	gotoxy(*pX, *pY);
	printf("【%s :lv %d:性質 %s】:%s\n", pAttacker->NAME,  pAttacker->LEVEL,  pAttacker->ATTRIBUTE,  pAttacker->JOB);
	*pY = wherey();
	gotoxy(*pX, *pY);
	printf("【体力:%3d　攻撃力%d　防御力%d　魔力%d　魔防%d　素早さ%d　運%d SP:%d】\n\n",  pAttacker->LIFE,  pAttacker->ATK,  pAttacker->DEF,  pAttacker->MATK,  pAttacker->MDEF,  pAttacker->SPD,  pAttacker->LUCK,  pAttacker->SIKLL_POINT);
	*pY = wherey();
	textcolor(WHITE);
	if (pDefender->LIFE < (*pPlayerMaxLife / 2) || pDefender->LIFE < (*pEnemyMaxLife / 2))
	{
		textcolor(YELLOW);
	}
	if (pDefender->LIFE < (*pPlayerMaxLife / 3) || pDefender->LIFE < (*pEnemyMaxLife / 3))
	{
		textcolor(LIGHTRED);
	}
	gotoxy(*pX, *pY);
	printf("【%s :lv %d:性質 %s】:%s\n", pDefender->NAME, pDefender->LEVEL, pDefender->ATTRIBUTE, pDefender->JOB);
	*pY = wherey();
	gotoxy(*pX, *pY);
	printf("【体力:%3d　攻撃力%d　防御力%d　魔力%d　魔防%d　素早さ%d　運%d SP:%d】\n\n", pDefender->LIFE, pDefender->ATK, pDefender->DEF, pDefender->MATK, pDefender->MDEF, pDefender->SPD, pDefender->LUCK, pDefender->SIKLL_POINT);
	textcolor(WHITE);
}
//=============================
// アクション
//=============================
void action(STATUS* pAttacker, SKILL_STUCK* pSkill, STATUS* pDefender, int* pDamage, int* pPhyFrag, int* pMagFrag, int* pLuckLimit, int* pDefLimit, int* pBuff, int* pX, int* pY, int* pCritFrag, int* pPlayerMaxLife, int* pEnemyMaxLife, int* pSkillSel)
{
	int criticalSkillDamage = 0, skillDamage = 0, statusUp = 0;
	srand((unsigned int)time(NULL));
	while (1)
	{
		rewind(stdin);
		system("cls");
		//現在のプレイヤー、エネミーのステータスの表示
		*pX = 65, * pY = 5;
		battleView(pAttacker, pDefender, pX, pY, pPlayerMaxLife, pEnemyMaxLife);
		*pX = 15, * pY = 5;
		viewSkill(pSkill, pX, pY);
		gotoxy(*pX, *pY);
		printf("どのスキルを使いますか？＞");
		scanf("%d", &*pSkillSel);//スキル選択
		*pY = *pY + 2;
		*pSkillSel -= 1;
		pAttacker->SIKLL_POINT -= (pSkill + *pSkillSel)->SKILL_DEL;//SP消費
		//各スキル処理//
		if (pAttacker->SIKLL_POINT > 0)
		{
			if (*pSkillSel >= 0 && *pSkillSel <= 2)
			{
				if ((pSkill + *pSkillSel)->SKILL_IDEN_NUM == kaenzan)
				{
					if (pDefender->ATTRIBUTE_NUM == fire)
					{
						criticalSkillDamage = pAttacker->ATK * 1.2f - (pDefender->DEF / (rand() % 3 + 2));
						skillDamage = pAttacker->ATK - (pDefender->DEF / (rand() % 2 + 2));
					}
					else if (pDefender->ATTRIBUTE_NUM == thunder)
					{
						criticalSkillDamage = (pAttacker->ATK * 1.2f - (pDefender->DEF / (rand() % 3 + 2))) + 1.2f;
						skillDamage = (pAttacker->ATK - (pDefender->DEF / (rand() % 2 + 2))) * 1.2f;
					}
					else if (pDefender->ATTRIBUTE_NUM == soil)
					{
						criticalSkillDamage = (pAttacker->ATK * 1.2f - (pDefender->DEF / (rand() % 3 + 2))) + 0.8f;
						skillDamage = (pAttacker->ATK - (pDefender->DEF / (rand() % 2 + 2))) * 0.8f;
					}
					else if (pDefender->ATTRIBUTE_NUM == normal)
					{
						criticalSkillDamage = pAttacker->ATK * 1.2f - (pDefender->DEF / (rand() % 3 + 2));
						skillDamage = pAttacker->ATK - (pDefender->DEF / (rand() % 2 + 2));
					}
				}
				else if ((pSkill + *pSkillSel)->SKILL_IDEN_NUM == raimeizan)
				{
					if (pDefender->ATTRIBUTE_NUM == fire)
					{
						criticalSkillDamage = (pAttacker->ATK * 1.2f - (pDefender->DEF / (rand() % 3 + 2))) + 0.8f;
						skillDamage = (pAttacker->ATK - (pDefender->DEF / (rand() % 2 + 2))) * 0.8f;
					}
					else if (pDefender->ATTRIBUTE_NUM == thunder)
					{
						criticalSkillDamage = pAttacker->ATK * 1.2f - (pDefender->DEF / (rand() % 3 + 2));
						skillDamage = pAttacker->ATK - (pDefender->DEF / (rand() % 2 + 2));
					}
					else if (pDefender->ATTRIBUTE_NUM == soil)
					{
						criticalSkillDamage = (pAttacker->ATK * 1.2f - (pDefender->DEF / (rand() % 3 + 2))) + 1.2f;
						skillDamage = (pAttacker->ATK - (pDefender->DEF / (rand() % 2 + 2))) * 1.2f;
					}
					else if (pDefender->ATTRIBUTE_NUM == normal)
					{
						criticalSkillDamage = pAttacker->ATK * 1.2f - (pDefender->DEF / (rand() % 3 + 2));
						skillDamage = pAttacker->ATK - (pDefender->DEF / (rand() % 2 + 2));
					}
				}
				else if ((pSkill + *pSkillSel)->SKILL_IDEN_NUM == daitigiri)
				{
					if (pDefender->ATTRIBUTE_NUM == fire)
					{
						criticalSkillDamage = (pAttacker->ATK * 1.2f - (pDefender->DEF / (rand() % 3 + 2))) + 1.2f;
						skillDamage = (pAttacker->ATK - (pDefender->DEF / (rand() % 2 + 2))) * 1.2f;
					}
					else if (pDefender->ATTRIBUTE_NUM == thunder)
					{
						criticalSkillDamage = (pAttacker->ATK * 1.2f - (pDefender->DEF / (rand() % 3 + 2))) + 0.8f;
						skillDamage = (pAttacker->ATK - (pDefender->DEF / (rand() % 2 + 2))) * 0.8f;
					}
					else if (pDefender->ATTRIBUTE_NUM == soil)
					{
						criticalSkillDamage = pAttacker->ATK * 1.2f - (pDefender->DEF / (rand() % 3 + 2));
						skillDamage = pAttacker->ATK - (pDefender->DEF / (rand() % 2 + 2));
					}
					else if (pDefender->ATTRIBUTE_NUM == normal)
					{
						criticalSkillDamage = pAttacker->ATK * 1.2f - (pDefender->DEF / (rand() % 3 + 2));
						skillDamage = pAttacker->ATK - (pDefender->DEF / (rand() % 2 + 2));
					}
				}
				else if ((pSkill + *pSkillSel)->SKILL_IDEN_NUM == kaen)
				{
					if (pDefender->ATTRIBUTE_NUM == fire)
					{
						criticalSkillDamage = pAttacker->MATK * 1.2f - (pDefender->MDEF / (rand() % 3 + 2));
						skillDamage = pAttacker->MATK - (pDefender->MDEF / (rand() % 2 + 2));
					}
					else if (pDefender->ATTRIBUTE_NUM == thunder)
					{
						criticalSkillDamage = (pAttacker->MATK * 1.2f - (pDefender->MDEF / (rand() % 3 + 2))) * 1.2f;
						skillDamage = (pAttacker->MATK - (pDefender->MDEF / (rand() % 2 + 2))) * 1.2f;
					}
					else if (pDefender->ATTRIBUTE_NUM == soil)
					{
						criticalSkillDamage = (pAttacker->MATK * 1.2f - (pDefender->MDEF / (rand() % 3 + 2))) * 0.8f;
						skillDamage = (pAttacker->MATK - (pDefender->MDEF / (rand() % 2 + 2))) * 0.8f;
					}
					else if (pDefender->ATTRIBUTE_NUM == normal)
					{
						criticalSkillDamage = pAttacker->MATK * 1.2f - (pDefender->MDEF / (rand() % 3 + 2));
						skillDamage = pAttacker->MATK - (pDefender->MDEF / (rand() % 2 + 2));
					}
				}
				else if ((pSkill + *pSkillSel)->SKILL_IDEN_NUM == raigeki)
				{
					if (pDefender->ATTRIBUTE_NUM == fire)
					{
						criticalSkillDamage = (pAttacker->MATK * 1.2f - (pDefender->MDEF / (rand() % 3 + 2))) * 0.8f;
						skillDamage = (pAttacker->MATK - (pDefender->MDEF / (rand() % 2 + 2))) * 0.8f;
					}
					else if (pDefender->ATTRIBUTE_NUM == thunder)
					{
						criticalSkillDamage = pAttacker->MATK * 1.2f - (pDefender->MDEF / (rand() % 3 + 2));
						skillDamage = pAttacker->MATK - (pDefender->MDEF / (rand() % 2 + 2));
					}
					else if (pDefender->ATTRIBUTE_NUM == soil)
					{
						criticalSkillDamage = (pAttacker->MATK * 1.2f - (pDefender->MDEF / (rand() % 3 + 2))) * 1.2f;
						skillDamage = (pAttacker->MATK - (pDefender->MDEF / (rand() % 2 + 2))) * 1.2f;
					}
					else if (pDefender->ATTRIBUTE_NUM == normal)
					{
						criticalSkillDamage = pAttacker->MATK * 1.2f - (pDefender->MDEF / (rand() % 3 + 2));
						skillDamage = pAttacker->MATK - (pDefender->MDEF / (rand() % 2 + 2));
					}
				}
				else if ((pSkill + *pSkillSel)->SKILL_IDEN_NUM == rakuseki)
				{
					if (pDefender->ATTRIBUTE_NUM == fire)
					{
						criticalSkillDamage = (pAttacker->MATK * 1.2f - (pDefender->MDEF / (rand() % 3 + 2))) * 1.2f;
						skillDamage = (pAttacker->MATK - (pDefender->MDEF / (rand() % 2 + 2))) * 1.2f;
					}
					else if (pDefender->ATTRIBUTE_NUM == thunder)
					{
						criticalSkillDamage = (pAttacker->MATK * 1.2f - (pDefender->MDEF / (rand() % 3 + 2))) * 0.8f;
						skillDamage = (pAttacker->MATK - (pDefender->MDEF / (rand() % 2 + 2))) * 0.8f;
					}
					else if (pDefender->ATTRIBUTE_NUM == soil)
					{
						criticalSkillDamage = pAttacker->MATK * 1.2f - (pDefender->MDEF / (rand() % 3 + 2));
						skillDamage = pAttacker->MATK - (pDefender->MDEF / (rand() % 2 + 2));
					}
					else if (pDefender->ATTRIBUTE_NUM == normal)
					{
						criticalSkillDamage = pAttacker->MATK * 1.2f - (pDefender->MDEF / (rand() % 3 + 2));
						skillDamage = pAttacker->MATK - (pDefender->MDEF / (rand() % 2 + 2));
					}
				}
				else if ((pSkill + *pSkillSel)->SKILL_IDEN_NUM == gougeki)
				{
					criticalSkillDamage = (pAttacker->ATK * 1.2f - (pDefender->DEF / (rand() % 3 + 2))) * 1.1f;
					skillDamage = (pAttacker->ATK - (pDefender->DEF / (rand() % 2 + 2))) * 1.1f;
				}
				else if ((pSkill + *pSkillSel)->SKILL_IDEN_NUM == tujigkiri)
				{
					criticalSkillDamage = (pAttacker->ATK * 1.2f - (pDefender->DEF / (rand() % 3 + 2))) + pAttacker->SPD / 2;
					skillDamage = (pAttacker->ATK - (pDefender->DEF / (rand() % 2 + 2))) + pAttacker->SPD / 2;
				}
				else if ((pSkill + *pSkillSel)->SKILL_IDEN_NUM == hosifuri)
				{
					if (rand() % (pAttacker->LUCK / 3) > rand() % (pAttacker->LUCK))
					{
						criticalSkillDamage = (pAttacker->MATK * 1.2f - (pDefender->MDEF / (rand() % 3 + 2))) * 1.5f;
						skillDamage = (pAttacker->MATK - (pDefender->MDEF / (rand() % 2 + 2))) * 1.5f;
					}
					else
					{
						gotoxy(*pX, *pY);
						printf("何も起こらなかった▽");
						*pY = wherey(),*pX=wherex();
						*pBuff = 1;
					}
				}
				else if ((pSkill + *pSkillSel)->SKILL_IDEN_NUM == kitou)
				{
					gotoxy(*pX, *pY);
					printf("スキル;祈祷\n");
					*pY = wherey();
					if (*pLuckLimit < 3)
					{
						statusUp = rand() % 11 + 5;
						pAttacker->LUCK += statusUp;
						gotoxy(*pX, *pY);
						printf("%sの運が%d上昇▽", pAttacker->NAME, statusUp);
						*pY = wherey(),*pX=wherex();
						gotoxy(*pX, *pY);
						*pLuckLimit += 1;
					}
					else
					{
						gotoxy(*pX, *pY);
						printf("これ以上は意味が無さそうだ...▽");
						*pY = wherey(),*pX=wherex();
						gotoxy(*pX, *pY);
					}
					*pBuff = 1;
				}
				else if ((pSkill + *pSkillSel)->SKILL_IDEN_NUM == goutai)
				{
					gotoxy(*pX, *pY);
					printf("スキル:剛体\n");
					*pY = wherey();
					if (*pDefLimit < 3)
					{
						statusUp = rand() % 11 + 5;
						pAttacker->DEF += statusUp;
						gotoxy(*pX, *pY);
						printf("%sの防御力が%d上昇\n", pAttacker->NAME, statusUp);
						*pY = wherey();
						statusUp = rand() % 11 + 5;
						pAttacker->MDEF += statusUp;
						gotoxy(*pX, *pY);
						printf("%sの魔防が%d上昇\n", pAttacker->NAME, statusUp);
						*pY = wherey();
						gotoxy(*pX, *pY);
						*pDefLimit += 1;
					}
					else
					{
						gotoxy(*pX, *pY);
						printf("これ以上は意味が無さそうだ...▽");
						*pY = wherey(),*pX=wherex();
						gotoxy(*pX, *pY);
					}
					*pBuff = 1;
				}
				else if ((pSkill + *pSkillSel)->SKILL_IDEN_NUM == kiaitame)
				{
					gotoxy(*pX, *pY);
					printf("スキル:気合ため\n");
					*pY = wherey();
					if (pPhyFrag == 0)
					{
						gotoxy(*pX, *pY);
						printf("次のターンまで攻撃力が上昇▽");
						*pY = wherey(),*pX=wherex();
						gotoxy(*pX, *pY);
						pAttacker->ATK += pAttacker->ATK / 2;
						*pPhyFrag = 1;
					}
					*pBuff = 1;
				}
				else if ((pSkill + *pSkillSel)->SKILL_IDEN_NUM == maryokutame)
				{
					gotoxy(*pX, *pY);
					printf("スキル:魔力ため\n");
					*pY = wherey();
					if (pMagFrag == 0)
					{
						gotoxy(*pX, *pY);
						printf("次のターンまで魔力が上昇▽");
						*pY = wherey(),*pX=wherex();
						gotoxy(*pX, *pY);
						pAttacker->MATK += pAttacker->MATK / 2;
						*pMagFrag = 1;
					}
					*pBuff = 1;
				}
				if ((pSkill + *pSkillSel)->SKILL_NAME[0] != '\0')
				{
					if (rand() % (pAttacker->LUCK / 2) > rand() % 100)
					{
						*pDamage = criticalSkillDamage;
						*pCritFrag = 1;
					}
					else
					{
						*pDamage = skillDamage;
						*pCritFrag = 0;
					}
				}
				else
				{
					gotoxy(*pX, *pY);
					printf("空回り▽");
					*pY = wherey(), *pX = wherex();
					gotoxy(*pX, *pY);
					*pBuff = 1;
				}
				rewind(stdin);
				break;
			}
			else
			{
				gotoxy(*pX, *pY);
				printf("そんなスキルの書はないぜ！▽");
				*pY = wherey(), * pX = wherex();
				gotoxy(*pX, *pY);
				clear();
			}
		}
		else
		{
			gotoxy(*pX, *pY);
			printf("スキルポイントが足りません▽");
			*pY = wherey(), * pX = wherex();
			gotoxy(*pX, *pY);
			*pBuff = 1;
			break;
		}
	}
}
//=============================
// レベルアップ
//=============================
void levelUp(STATUS* pPlayer, SKILL_STUCK* pSkill, int* pSkillCount, int* pExSel, int* pX, int* pY)
{
	int exp = 0, oldLevel = 0;
	srand((unsigned int)time(NULL));
	exp = rand() % 50 + 1;
	*pY = *pY + 2, *pX = 15;
	gotoxy(*pX, *pY);
	printf("%sは%dの経験値を手に入れた！\n", (pPlayer + *pExSel)->NAME, exp);
	*pY = wherey();
	(pPlayer + *pExSel)->EXP += exp;
	//レベルアップ、ステータス更新//
	if ((pPlayer + *pExSel)->EXP >= 100)
	{
		oldLevel = (pPlayer + *pExSel)->LEVEL;
		(pPlayer + *pExSel)->LEVEL += 1;
		gotoxy(*pX,*pY);
		printf("%sはレベルが1上がった\n", (pPlayer + *pExSel)->NAME);
		*pY = wherey();
		gotoxy(*pX, *pY);
		printf("(lv.%d → lv.%d)", oldLevel, (pPlayer + *pExSel)->LEVEL);
		*pY = wherey();
		clear();
		*pY = 5;
		if ((pPlayer + *pExSel)->JOBNUM == fighterNum)
		{
			(pPlayer + *pExSel)->LIFE += rand() % 21;
			(pPlayer + *pExSel)->ATK += rand() % 21;
			(pPlayer + *pExSel)->DEF += rand() % 11;
			(pPlayer + *pExSel)->MATK += rand() % 6;
			(pPlayer + *pExSel)->MDEF += rand() % 6;
			(pPlayer + *pExSel)->SPD += rand() % 21;
			skillFighter(pSkill, pSkillCount, pX, pY);
		}
		else if ((pPlayer + *pExSel)->JOBNUM == tankNum)
		{
			(pPlayer + *pExSel)->LIFE += rand() % 21;
			(pPlayer + *pExSel)->ATK += rand() % 11;
			(pPlayer + *pExSel)->DEF += rand() % 21;
			(pPlayer + *pExSel)->MATK += rand() % 6;
			(pPlayer + *pExSel)->MDEF += rand() % 21;
			(pPlayer + *pExSel)->SPD += rand() % 6;
			skillTank(pSkill, pSkillCount, pX, pY);
		}
		else if ((pPlayer + *pExSel)->JOBNUM == wizardNum)
		{
			(pPlayer + *pExSel)->LIFE += rand() % 6;
			(pPlayer + *pExSel)->ATK += rand() % 11;
			(pPlayer + *pExSel)->DEF += rand() % 11;
			(pPlayer + *pExSel)->MATK += rand() % 21;
			(pPlayer + *pExSel)->MDEF += rand() % 21;
			(pPlayer + *pExSel)->SPD += rand() % 6;
			skillWizard(pSkill, pSkillCount, pX, pY);
		}
		else if ((pPlayer + *pExSel)->JOBNUM == assassinNum)
		{
			(pPlayer + *pExSel)->LIFE += rand() % 6;
			(pPlayer + *pExSel)->ATK += rand() % 21;
			(pPlayer + *pExSel)->DEF += rand() % 6;
			(pPlayer + *pExSel)->MATK += rand() % 21;
			(pPlayer + *pExSel)->MDEF += rand() % 11;
			(pPlayer + *pExSel)->SPD += rand() % 21;
			skillAssassin(pSkill, pSkillCount, pX, pY);
		}
		(pPlayer + *pExSel)->SIKLL_POINT += rand() % 6;
		(pPlayer + *pExSel)->EXP = 0;
		*pY = *pY + 1;
	}
}
//=============================
// スキル:ファイター
//=============================
void skillFighter(SKILL_STUCK* pSkill, int* pSkillCount, int* pX, int* pY)
{
	int randSkill = 0;
	int check = 0;
	int bookNum = 0;
	srand((unsigned int)time(NULL));
	//ジョブ別スキル取得//
	if (rand() % 200 <= 19)
	{
		if (pSkillCount[skill1] == 0 && rand() % 200 >= 0 && rand() % 200 <= 19)
		{
			gotoxy(*pX, *pY);
			printf("スキル:火炎斬 性質:火 消費SP:10\n");
			*pY = wherey();
			gotoxy(*pX, *pY);
			printf("このスキルを覚えますか？(はい:1/いいえ:2)＞");
			scanf("%d",&check);
			*pY = *pY + 1;
			if (check == 1)
			{
				while (1)
				{
					viewSkill(pSkill, pX, pY);
					gotoxy(*pX, *pY);
					printf("どこの書に記入しますか?＞");
					scanf("%d", &bookNum);
					*pY = *pY + 1;
					bookNum--;
					if (bookNum >= 0 && bookNum <= 2)
					{
						strcpy((pSkill + bookNum)->SKILL_NAME, "火炎斬");
						strcpy((pSkill + bookNum)->SKILL_ATTRIBUTE, "火");
						(pSkill + bookNum)->SKILL_AT_NUM = fire;
						(pSkill + bookNum)->SKILL_DEL = 10;
						(pSkill + bookNum)->SKILL_IDEN_NUM = kaenzan;
						pSkillCount[skill1] = 1;
						break;
					}
					else
					{
						gotoxy(*pX, *pY);
						printf("そんな書は存在しないぜ！");
						clear();
						*pY = 1;
					}
				}
			}
			else
			{
			}
		}
	}
	else if (rand() % 200 >= 20 && rand() % 200 <= 39 && pSkillCount[skill2] == 0)
	{
		if (pSkillCount[skill2] == 0)
		{
			gotoxy(*pX, *pY);
			printf("スキル:雷鳴斬 性質:雷 消費SP:10\n");
			*pY = wherey();
			gotoxy(*pX, *pY);
			printf("このスキルを覚えますか？(はい:1/いいえ:2)＞");
			scanf("%d", &check);
			*pY = *pY + 1;
			if (check == 1)
			{
				while (1)
				{
					viewSkill(pSkill, pX, pY);
					gotoxy(*pX, *pY);
					printf("どこの書に記入しますか?＞");
					scanf("%d", &bookNum);
					*pY = *pY + 1;
					bookNum--;
					if (bookNum >= 0 && bookNum <= 2)
					{
						strcpy((pSkill+bookNum)->SKILL_NAME, "雷鳴斬");
						strcpy((pSkill + bookNum)->SKILL_ATTRIBUTE, "雷");
						(pSkill + bookNum)->SKILL_AT_NUM = thunder;
						(pSkill + bookNum)->SKILL_DEL = 10;
						(pSkill + bookNum)->SKILL_IDEN_NUM = raimeizan;
						pSkillCount[skill2] = 1;
						break;
					}
					else
					{
						gotoxy(*pX, *pY);
						printf("そんな書は存在しないぜ！");
						clear();
						*pY = 1;
					}
				}
			}
			else
			{
			}
		}
	}
	else if (rand() % 200 >= 40 && rand() % 200 <= 59 && pSkillCount[skill3] == 0)
	{
		if (pSkillCount[skill3] == 0)
		{
			gotoxy(*pX, *pY);
			printf("スキル:大地斬 性質:土 消費SP:10\n");
			*pY = wherey();
			gotoxy(*pX, *pY);
			printf("このスキルを覚えますか？(はい:1/いいえ:2)＞");
			scanf("%d", &check);
			*pY = *pY + 1;
			if (check == 1)
			{
				while (1)
				{
					viewSkill(pSkill, pX, pY);
					gotoxy(*pX, *pY);
					printf("どこの書に記入しますか?＞");
					scanf("%d", &bookNum);
					*pY = *pY + 1;
					bookNum--;
					if (bookNum >= 0 && bookNum <= 2)
					{
						strcpy((pSkill + bookNum)->SKILL_NAME, "大地斬");
						strcpy((pSkill + bookNum)->SKILL_ATTRIBUTE, "土");
						(pSkill + bookNum)->SKILL_AT_NUM = soil;
						(pSkill + bookNum)->SKILL_DEL = 10;
						(pSkill + bookNum)->SKILL_IDEN_NUM = daitigiri;
						pSkillCount[skill3] = 1;
						break;
					}
					else
					{
						gotoxy(*pX, *pY);
						printf("そんな書は存在しないぜ！");
						clear();
						*pY = 1;
					}
				}
			}
			else
			{
			}
		}
	}
	else if (rand() % 200 >= 60 && rand() % 200 <= 79 && pSkillCount[skill4] == 0)
	{
		if (pSkillCount[skill4] == 0)
		{
			gotoxy(*pX, *pY);
			printf("スキル:剛撃 性質:無 消費SP:20\n");
			*pY = wherey();
			gotoxy(*pX, *pY);
			printf("このスキルを覚えますか？(はい:1/いいえ:2)＞");
			scanf("%d", &check);
			*pY = *pY + 1;
			if (check == 1)
			{
				while (1)
				{
					viewSkill(pSkill, pX, pY);
					gotoxy(*pX, *pY);
					printf("どこの書に記入しますか?＞");
					scanf("%d", &bookNum);
					*pY = *pY + 1;
					bookNum--;
					if (bookNum >= 0 && bookNum <= 2)
					{
						strcpy((pSkill + bookNum)->SKILL_NAME, "剛撃");
						strcpy((pSkill + bookNum)->SKILL_ATTRIBUTE, "無");
						(pSkill + bookNum)->SKILL_AT_NUM = normal;
						(pSkill + bookNum)->SKILL_DEL = 20;
						(pSkill + bookNum)->SKILL_IDEN_NUM = gougeki;
						pSkillCount[skill4] = 1;
						break;
					}
					else
					{
						gotoxy(*pX, *pY);
						printf("そんな書は存在しないぜ！");
						clear();
						*pY = 1;
					}
				}
			}
			else
			{
			}
		}
	}
	else if (rand() % 200 >= 80 && rand() % 200 <= 99 && pSkillCount[skill5] == 0)
	{
		if (pSkillCount[skill5] == 0)
		{
			gotoxy(*pX, *pY);
			printf("スキル:気合ため 性質:無 消費SP:20\n");
			*pY = wherey();
			gotoxy(*pX, *pY);
			printf("このスキルを覚えますか？(はい:1/いいえ:2)＞");
			scanf("%d", &check);
			*pY = *pY + 1;
			if (check == 1)
			{
				while (1)
				{
					viewSkill(pSkill, pX, pY);
					gotoxy(*pX, *pY);
					printf("どこの書に記入しますか?＞");
					scanf("%d", &bookNum);
					*pY = *pY + 1;
					bookNum--;
					if (bookNum >= 0 && bookNum <= 2)
					{
						strcpy((pSkill + bookNum)->SKILL_NAME, "気合ため");
						strcpy((pSkill + bookNum)->SKILL_ATTRIBUTE, "無");
						(pSkill + bookNum)->SKILL_AT_NUM = normal;
						(pSkill + bookNum)->SKILL_DEL = 20;
						pSkillCount[skill5] = 1;
						(pSkill + bookNum)->SKILL_IDEN_NUM = kiaitame;
						break;
					}
					else
					{
						gotoxy(*pX, *pY);
						printf("そんな書は存在しないぜ！");
						clear();
						*pY = 1;
					}
				}
			}
		}
	}
	else
	{
	}
}
//=============================
// スキル:タンク
//=============================
void skillTank(SKILL_STUCK* pSkill, int* pSkillCount, int* pX, int* pY)
{
	int randSkill = 0;
	int check = 0;
	int bookNum = 0;
	srand((unsigned int)time(NULL));
	//ジョブ別スキル取得//
	if (rand() % 200 <= 19)
	{
		if (pSkillCount[skill1] == 0 && rand() % 200 >= 0 && rand() % 200 <= 19)
		{
			gotoxy(*pX, *pY);
			printf("スキル:火炎斬 性質:火 消費SP:10\n");
			*pY = wherey();
			gotoxy(*pX, *pY);
			printf("このスキルを覚えますか？(はい:1/いいえ:2)＞");
			scanf("%d", &check);
			*pY = *pY + 1;
			if (check == 1)
			{
				while (1)
				{
					viewSkill(pSkill, pX, pY);
					gotoxy(*pX, *pY);
					printf("どこの書に記入しますか?＞");
					scanf("%d", &bookNum);
					*pY = *pY + 1;
					bookNum--;
					if (bookNum >= 0 && bookNum <= 2)
					{
						strcpy((pSkill + bookNum)->SKILL_NAME, "火炎斬");
						strcpy((pSkill + bookNum)->SKILL_ATTRIBUTE, "火");
						(pSkill + bookNum)->SKILL_AT_NUM = fire;
						(pSkill + bookNum)->SKILL_DEL = 10;
						(pSkill + bookNum)->SKILL_IDEN_NUM = kaenzan;
						pSkillCount[skill1] = 1;
						break;
					}
					else
					{
						gotoxy(*pX, *pY);
						printf("そんな書は存在しないぜ！");
						clear();
						*pY = 1;
					}
				}
			}
			else
			{
			}
		}
	}
	else if (rand() % 200 >= 20 && rand() % 200 <= 39 && pSkillCount[skill2] == 0)
	{
		if (pSkillCount[skill2] == 0)
		{
			gotoxy(*pX, *pY);
			printf("スキル:大地斬 性質:土 消費SP:10\n");
			*pY = wherey();
			gotoxy(*pX, *pY);
			printf("このスキルを覚えますか？(はい:1/いいえ:2)＞");
			scanf("%d", &check);
			*pY = *pY + 1;
			if (check == 1)
			{
				while (1)
				{
					viewSkill(pSkill, pX, pY);
					gotoxy(*pX, *pY);
					printf("どこの書に記入しますか?＞");
					scanf("%d", &bookNum);
					*pY = *pY + 1;
					bookNum--;
					if (bookNum >= 0 && bookNum <= 2)
					{
						strcpy((pSkill + bookNum)->SKILL_NAME, "大地斬");
						strcpy((pSkill + bookNum)->SKILL_ATTRIBUTE, "土");
						(pSkill + bookNum)->SKILL_AT_NUM = soil;
						(pSkill + bookNum)->SKILL_DEL = 10;
						(pSkill + bookNum)->SKILL_IDEN_NUM = daitigiri;
						pSkillCount[skill2] = 1;
						break;
					}
					else
					{
						gotoxy(*pX, *pY);
						printf("そんな書は存在しないぜ！");
						clear();
						*pY = 1;
					}
				}
			}
			else
			{
			}
		}
	}
	else if (rand() % 200 >= 40 && rand() % 200 <= 59 && pSkillCount[skill3] == 0)
	{
		if (pSkillCount[skill3] == 0)
		{
			gotoxy(*pX, *pY);
			printf("スキル:祈祷 性質:無 消費SP:15\n");
			*pY = wherey();
			gotoxy(*pX, *pY);
			printf("このスキルを覚えますか？(はい:1/いいえ:2)＞");
			scanf("%d", &check);
			*pY = *pY + 1;
			if (check == 1)
			{
				while (1)
				{
					viewSkill(pSkill, pX, pY);
					gotoxy(*pX, *pY);
					printf("どこの書に記入しますか?＞");
					scanf("%d", &bookNum);
					*pY = *pY + 1;
					bookNum--;
					if (bookNum >= 0 && bookNum <= 2)
					{
						strcpy((pSkill + bookNum)->SKILL_NAME, "祈祷");
						strcpy((pSkill + bookNum)->SKILL_ATTRIBUTE, "無");
						(pSkill + bookNum)->SKILL_AT_NUM = normal;
						(pSkill + bookNum)->SKILL_DEL = 10;
						(pSkill + bookNum)->SKILL_IDEN_NUM = kitou;
						pSkillCount[skill3] = 1;
						break;
					}
					else
					{
						gotoxy(*pX, *pY);
						printf("そんな書は存在しないぜ！");
						clear();
						*pY = 1;
					}
				}
			}
			else
			{
			}
		}
	}
	else if (rand() % 200 >= 60 && rand() % 200 <= 79 && pSkillCount[skill4] == 0)
	{
		if (pSkillCount[skill4] == 0)
		{
			gotoxy(*pX, *pY);
			printf("スキル:剛撃 性質:無 消費SP:20\n");
			*pY = wherey();
			gotoxy(*pX, *pY);
			printf("このスキルを覚えますか？(はい:1/いいえ:2)＞");
			scanf("%d", &check);
			*pY = *pY + 1;
			if (check == 1)
			{
				while (1)
				{
					viewSkill(pSkill, pX, pY);
					gotoxy(*pX, *pY);
					printf("どこの書に記入しますか?＞");
					scanf("%d", &bookNum);
					*pY = *pY + 1;
					bookNum--;
					if (bookNum >= 0 && bookNum <= 2)
					{
						strcpy((pSkill + bookNum)->SKILL_NAME, "剛撃");
						strcpy((pSkill + bookNum)->SKILL_ATTRIBUTE, "無");
						(pSkill + bookNum)->SKILL_AT_NUM = normal;
						(pSkill + bookNum)->SKILL_DEL = 20;
						(pSkill + bookNum)->SKILL_IDEN_NUM = gougeki;
						pSkillCount[skill4] = 1;
						break;
					}
					else
					{
						gotoxy(*pX, *pY);
						printf("そんな書は存在しないぜ！");
						clear();
						*pY = 1;
					}
				}
			}
			else
			{
			}
		}
	}
	else if (rand() % 200 >= 80 && rand() % 200 <= 99 && pSkillCount[skill5] == 0)
	{
		if (pSkillCount[skill5] == 0)
		{
			gotoxy(*pX, *pY);
			printf("スキル:剛体 性質:無 消費SP:20\n");
			*pY = wherey();
			gotoxy(*pX, *pY);
			printf("このスキルを覚えますか？(はい:1/いいえ:2)＞");
			scanf("%d", &check);
			*pY = *pY + 1;
			if (check == 1)
			{
				while (1)
				{
					viewSkill(pSkill, pX, pY);
					gotoxy(*pX, *pY);
					printf("どこの書に記入しますか?＞");
					scanf("%d", &bookNum);
					*pY = *pY + 1;
					bookNum--;
					if (bookNum >= 0 && bookNum <= 2)
					{
						strcpy((pSkill + bookNum)->SKILL_NAME, "剛体");
						strcpy((pSkill + bookNum)->SKILL_ATTRIBUTE, "無");
						(pSkill + bookNum)->SKILL_AT_NUM = normal;
						(pSkill + bookNum)->SKILL_DEL = 20;
						(pSkill + bookNum)->SKILL_IDEN_NUM = goutai;
						pSkillCount[skill5] = 1;
						break;
					}
					else
					{
						gotoxy(*pX, *pY);
						printf("そんな書は存在しないぜ！");
						clear();
						*pY = 1;
					}
				}
			}
		}
	}
	else
	{
	}
}
//=============================
// スキル:ウィザード
//=============================
void skillWizard(SKILL_STUCK* pSkill, int* pSkillCount, int* pX, int* pY)
{
	int randSkill = 0;
	int check = 0;
	int bookNum = 0;
	srand((unsigned int)time(NULL));
	//ジョブ別スキル取得//
	if (rand() % 200 <= 19)
	{
		if (pSkillCount[skill1] == 0 && rand() % 200 >= 0 && rand() % 200 <= 19)
		{
			gotoxy(*pX, *pY);
			printf("スキル:祈祷 性質:無 消費SP:15\n");
			*pY = wherey();
			gotoxy(*pX, *pY);
			printf("このスキルを覚えますか？(はい:1/いいえ:2)＞");
			scanf("%d", &check);
			*pY = *pY + 1;
			if (check == 1)
			{
				while (1)
				{
					viewSkill(pSkill, pX, pY);
					gotoxy(*pX, *pY);
					printf("どこの書に記入しますか?＞");
					scanf("%d", &bookNum);
					*pY = *pY + 1;
					bookNum--;
					if (bookNum >= 0 && bookNum <= 2)
					{
						strcpy((pSkill + bookNum)->SKILL_NAME, "祈祷");
						strcpy((pSkill + bookNum)->SKILL_ATTRIBUTE, "無");
						(pSkill + bookNum)->SKILL_AT_NUM = normal;
						(pSkill + bookNum)->SKILL_DEL = 15;
						(pSkill + bookNum)->SKILL_IDEN_NUM = kitou;
						pSkillCount[skill1] = 1;
						break;
					}
					else
					{
						gotoxy(*pX, *pY);
						printf("そんな書は存在しないぜ！");
						clear();
						*pY = 1;
					}
				}
			}
			else
			{
			}
		}
	}
	else if (rand() % 200 >= 20 && rand() % 200 <= 39 && pSkillCount[skill2] == 0)
	{
		if (pSkillCount[skill2] == 0)
		{
			gotoxy(*pX, *pY);
			printf("スキル:火炎 性質:火 消費SP:10\n");
			*pY = wherey();
			gotoxy(*pX, *pY);
			printf("このスキルを覚えますか？(はい:1/いいえ:2)＞");
			scanf("%d", &check);
			*pY = *pY + 1;
			if (check == 1)
			{
				while (1)
				{
					viewSkill(pSkill, pX, pY);
					gotoxy(*pX, *pY);
					printf("どこの書に記入しますか?＞");
					scanf("%d", &bookNum);
					*pY = *pY + 1;
					bookNum--;
					if (bookNum >= 0 && bookNum <= 2)
					{
						strcpy((pSkill + bookNum)->SKILL_NAME, "火炎");
						strcpy((pSkill + bookNum)->SKILL_ATTRIBUTE, "火");
						(pSkill + bookNum)->SKILL_AT_NUM = fire;
						(pSkill + bookNum)->SKILL_DEL = 10;
						(pSkill + bookNum)->SKILL_IDEN_NUM = kaen;
						pSkillCount[skill2] = 1;
						break;
					}
					else
					{
						gotoxy(*pX, *pY);
						printf("そんな書は存在しないぜ！");
						clear();
						*pY = 1;
					}
				}
			}
			else
			{
			}
		}
	}
	else if (rand() % 200 >= 40 && rand() % 200 <= 59 && pSkillCount[skill3] == 0)
	{
		if (pSkillCount[skill3] == 0)
		{
			gotoxy(*pX, *pY);
			printf("スキル:星降り 性質:土 消費SP:20\n");
			*pY = wherey();
			gotoxy(*pX, *pY);
			printf("このスキルを覚えますか？(はい:1/いいえ:2)＞");
			scanf("%d", &check);
			*pY = *pY + 1;
			if (check == 1)
			{
				while (1)
				{
					viewSkill(pSkill, pX, pY);
					gotoxy(*pX, *pY);
					printf("どこの書に記入しますか?＞");
					scanf("%d", &bookNum);
					*pY = *pY + 1;
					bookNum--;
					if (bookNum >= 0 && bookNum <= 2)
					{
						strcpy((pSkill + bookNum)->SKILL_NAME, "星降り");
						strcpy((pSkill + bookNum)->SKILL_ATTRIBUTE, "無");
						(pSkill + bookNum)->SKILL_AT_NUM = normal;
						(pSkill + bookNum)->SKILL_DEL = 20;
						(pSkill + bookNum)->SKILL_IDEN_NUM = hosifuri;
						pSkillCount[skill3] = 1;
						break;
					}
					else
					{
						gotoxy(*pX, *pY);
						printf("そんな書は存在しないぜ！");
						clear();
						*pY = 1;
					}
				}
			}
			else
			{
			}
		}
	}
	else if (rand() % 200 >= 60 && rand() % 200 <= 79 && pSkillCount[skill4] == 0)
	{
		if (pSkillCount[skill4] == 0)
		{
			gotoxy(*pX, *pY);
			printf("スキル:雷撃 性質:雷 消費SP:10\n");
			*pY = wherey();
			gotoxy(*pX, *pY);
			printf("このスキルを覚えますか？(はい:1/いいえ:2)＞");
			scanf("%d", &check);
			*pY = *pY + 1;
			if (check == 1)
			{
				while (1)
				{
					viewSkill(pSkill, pX, pY);
					gotoxy(*pX, *pY);
					printf("どこの書に記入しますか?＞");
					scanf("%d", &bookNum);
					*pY = *pY + 1;
					bookNum--;
					if (bookNum >= 0 && bookNum <= 2)
					{
						strcpy((pSkill + bookNum)->SKILL_NAME, "雷撃");
						strcpy((pSkill + bookNum)->SKILL_ATTRIBUTE, "雷");
						(pSkill + bookNum)->SKILL_AT_NUM = thunder;
						(pSkill + bookNum)->SKILL_DEL = 10;
						(pSkill + bookNum)->SKILL_IDEN_NUM = raigeki;
						pSkillCount[skill4] = 1;
						break;
					}
					else
					{
						gotoxy(*pX, *pY);
						printf("そんな書は存在しないぜ！");
						clear();
						*pY = 1;
					}
				}
			}
			else
			{
			}
		}
	}
	else if (rand() % 200 >= 80 && rand() % 200 <= 99 && pSkillCount[skill5] == 0)
	{
		if (pSkillCount[skill5] == 0)
		{
			gotoxy(*pX, *pY);
			printf("スキル:魔力ため 性質:無 消費SP:20\n");
			*pY = wherey();
			gotoxy(*pX, *pY);
			printf("このスキルを覚えますか？(はい:1/いいえ:2)＞");
			scanf("%d", &check);
			*pY = *pY + 1;
			if (check == 1)
			{
				while (1)
				{
					viewSkill(pSkill, pX, pY);
					gotoxy(*pX, *pY);
					printf("どこの書に記入しますか?＞");
					scanf("%d", &bookNum);
					*pY = *pY + 1;
					bookNum--;
					if (bookNum >= 0 && bookNum <= 2)
					{
						strcpy((pSkill + bookNum)->SKILL_NAME, "魔力ため");
						strcpy((pSkill + bookNum)->SKILL_ATTRIBUTE, "無");
						(pSkill + bookNum)->SKILL_AT_NUM = normal;
						(pSkill + bookNum)->SKILL_DEL = 20;
						(pSkill + bookNum)->SKILL_IDEN_NUM = maryokutame;
						pSkillCount[skill5] = 1;
						break;
					}
					else
					{
						gotoxy(*pX, *pY);
						printf("そんな書は存在しないぜ！");
						clear();
						*pY = 1;
					}
				}
			}
		}
	}
	else
	{
	}
}
//=============================
// スキル:アサシン
//=============================
void skillAssassin(SKILL_STUCK* pSkill, int* pSkillCount, int* pX, int* pY)
{
	int randSkill = 0;
	int check = 0;
	int bookNum = 0;
	srand((unsigned int)time(NULL));
	//ジョブ別スキル取得//
	if (rand() % 200 <= 19)
	{
		if (pSkillCount[skill1] == 0 && rand() % 200 >= 0 && rand() % 200 <= 19)
		{
			gotoxy(*pX, *pY);
			printf("スキル:火炎斬 性質:火 消費SP:10\n");
			*pY = wherey();
			gotoxy(*pX, *pY);
			printf("このスキルを覚えますか？(はい:1/いいえ:2)＞");
			scanf("%d", &check);
			*pY = *pY + 1;
			if (check == 1)
			{
				while (1)
				{
					viewSkill(pSkill, pX, pY);
					gotoxy(*pX, *pY);
					printf("どこの書に記入しますか?＞");
					scanf("%d", &bookNum);
					*pY = *pY + 1;
					bookNum--;
					if (bookNum >= 0 && bookNum <= 2)
					{
						strcpy((pSkill + bookNum)->SKILL_NAME, "火炎斬");
						strcpy((pSkill + bookNum)->SKILL_ATTRIBUTE, "火");
						(pSkill + bookNum)->SKILL_AT_NUM = fire;
						(pSkill + bookNum)->SKILL_DEL = 10;
						(pSkill + bookNum)->SKILL_IDEN_NUM = kaenzan;
						pSkillCount[skill1] = 1;
						break;
					}
					else
					{
						gotoxy(*pX, *pY);
						printf("そんな書は存在しないぜ！");
						clear();
						*pY = 1;
					}
				}
			}
			else
			{
			}
		}
	}
	else if (rand() % 200 >= 20 && rand() % 200 <= 39 && pSkillCount[skill2] == 0)
	{
		if (pSkillCount[skill2] == 0)
		{
			gotoxy(*pX, *pY);
			printf("スキル:雷鳴斬 性質:雷 消費SP:10\n");
			*pY = wherey();
			gotoxy(*pX, *pY);
			printf("このスキルを覚えますか？(はい:1/いいえ:2)＞");
			scanf("%d", &check);
			*pY = *pY + 1;
			if (check == 1)
			{
				while (1)
				{
					viewSkill(pSkill, pX, pY);
					gotoxy(*pX, *pY);
					printf("どこの書に記入しますか?＞");
					scanf("%d", &bookNum);
					*pY = *pY + 1;
					bookNum--;
					if (bookNum >= 0 && bookNum <= 2)
					{
						strcpy((pSkill + bookNum)->SKILL_NAME, "雷鳴斬");
						strcpy((pSkill + bookNum)->SKILL_ATTRIBUTE, "雷");
						(pSkill + bookNum)->SKILL_AT_NUM = thunder;
						(pSkill + bookNum)->SKILL_DEL = 10;
						(pSkill + bookNum)->SKILL_IDEN_NUM = raimeizan;
						pSkillCount[skill2] = 1;
						break;
					}
					else
					{
						gotoxy(*pX, *pY);
						printf("そんな書は存在しないぜ！");
						clear();
						*pY = 1;
					}
				}
			}
			else
			{
			}
		}
	}
	else if (rand() % 200 >= 40 && rand() % 200 <= 59 && pSkillCount[skill3] == 0)
	{
		if (pSkillCount[skill3] == 0)
		{
			gotoxy(*pX, *pY);
			printf("スキル:落石 性質:土 消費SP:10\n");
			*pY = wherey();
			gotoxy(*pX, *pY);
			printf("このスキルを覚えますか？(はい:1/いいえ:2)＞");
			scanf("%d", &check);
			*pY = *pY + 1;
			if (check == 1)
			{
				while (1)
				{
					viewSkill(pSkill, pX, pY);
					gotoxy(*pX, *pY);
					printf("どこの書に記入しますか?＞");
					scanf("%d", &bookNum);
					*pY = *pY + 1;
					bookNum--;
					if (bookNum >= 0 && bookNum <= 2)
					{
						strcpy((pSkill + bookNum)->SKILL_NAME, "大地斬");
						strcpy((pSkill + bookNum)->SKILL_ATTRIBUTE, "土");
						(pSkill + bookNum)->SKILL_AT_NUM = soil;
						(pSkill + bookNum)->SKILL_DEL = 10;
						(pSkill + bookNum)->SKILL_IDEN_NUM = daitigiri;
						pSkillCount[skill3] = 1;
						break;
					}
					else
					{
						gotoxy(*pX, *pY);
						printf("そんな書は存在しないぜ！");
						clear();
						*pY = 1;
					}
				}
			}
			else
			{
			}
		}
	}
	else if (rand() % 200 >= 60 && rand() % 200 <= 79 && pSkillCount[skill4] == 0)
	{
		if (pSkillCount[skill4] == 0)
		{
			gotoxy(*pX, *pY);
			printf("スキル:雷撃 性質:雷 消費SP:10\n");
			*pY = wherey();
			gotoxy(*pX, *pY);
			printf("このスキルを覚えますか？(はい:1/いいえ:2)＞");
			scanf("%d", &check);
			*pY = *pY + 1;
			if (check == 1)
			{
				while (1)
				{
					viewSkill(pSkill, pX, pY);
					gotoxy(*pX, *pY);
					printf("どこの書に記入しますか?＞");
					scanf("%d", &bookNum);
					*pY = *pY + 1;
					bookNum--;
					if (bookNum >= 0 && bookNum <= 2)
					{
						strcpy((pSkill + bookNum)->SKILL_NAME, "雷撃");
						strcpy((pSkill + bookNum)->SKILL_ATTRIBUTE, "雷");
						(pSkill + bookNum)->SKILL_AT_NUM = thunder;
						(pSkill + bookNum)->SKILL_DEL = 10;
						(pSkill + bookNum)->SKILL_IDEN_NUM = raigeki;
						pSkillCount[skill4] = 1;
						break;
					}
					else
					{
						gotoxy(*pX, *pY);
						printf("そんな書は存在しないぜ！");
						clear();
						*pY = 1;
					}
				}
			}
			else
			{
			}
		}
	}
	else if (rand() % 200 >= 80 && rand() % 200 <= 99 && pSkillCount[skill5] == 0)
	{
		if (pSkillCount[skill5] == 0)
		{
			gotoxy(*pX, *pY);
			printf("スキル:辻斬り 性質:無 消費SP:20\n");
			*pY = wherey();
			gotoxy(*pX, *pY);
			printf("このスキルを覚えますか？(はい:1/いいえ:2)＞");
			scanf("%d", &check);
			*pY = *pY + 1;
			if (check == 1)
			{
				while (1)
				{
					viewSkill(pSkill, pX, pY);
					gotoxy(*pX, *pY);
					printf("どこの書に記入しますか?＞");
					scanf("%d", &bookNum);
					*pY = *pY + 1;
					bookNum--;
					if (bookNum >= 0 && bookNum <= 2)
					{
						strcpy((pSkill + bookNum)->SKILL_NAME, "辻斬り");
						strcpy((pSkill + bookNum)->SKILL_ATTRIBUTE, "無");
						(pSkill + bookNum)->SKILL_AT_NUM = normal;
						(pSkill + bookNum)->SKILL_DEL = 20;
						(pSkill + bookNum)->SKILL_IDEN_NUM = tujigkiri;
						pSkillCount[skill5] = 1;
						break;
					}
					else
					{
						gotoxy(*pX, *pY);
						printf("そんな書は存在しないぜ！");
						clear();
						*pY = 1;
					}
				}
			}
		}
	}
	else
	{
	}
}
//=============================
// スキル:エネミー
//=============================(
void skillEnemy(STATUS* pAttacker, STATUS* pDefender, SKILL_STUCK* pSkill, int* pEnemyDamage, int* pBuff, int* pEnemyLuckLimit, int* pEnemyDefLimit, int* pPhyEFrag, int* pMagEFrag, int* pX, int* pY,int* pCritFrag)
{
	int eSkillDamage = 0, eCriticalSkillDamage = 0, enemyStatusUp = 0, change = 0, bossCount = 0, end = 0;
	srand((unsigned int)time(NULL));
	if (pAttacker->IDEN == enemyIdenNum)
	{
		if (pAttacker->JOBNUM == fighterNum)
		{
			if (rand() % 100 < 20)
			{
				strcpy(pSkill->SKILL_NAME, "火炎斬");
				pSkill->SKILL_AT_NUM == fire;
				if (pDefender->ATTRIBUTE_NUM == fire)
				{
					eCriticalSkillDamage = pAttacker->ATK * 1.2f - (pDefender->DEF / (rand() % 3 + 2));
					eSkillDamage = pAttacker->ATK - (pDefender->DEF / (rand() % 2 + 2));
				}
				else if (pDefender->ATTRIBUTE_NUM == thunder)
				{
					eCriticalSkillDamage = (pAttacker->ATK * 1.2f - (pDefender->DEF / (rand() % 3 + 2))) * 1.2f;
					eSkillDamage = (pAttacker->ATK - (pDefender->DEF / (rand() % 2 + 2)))*1.2f;
				}
				else if (pDefender->ATTRIBUTE_NUM == soil)
				{
					eCriticalSkillDamage = (pAttacker->ATK * 1.2f - (pDefender->DEF / (rand() % 3 + 2)))*0.8f;
					eSkillDamage = (pAttacker->ATK - (pDefender->DEF / (rand() % 2 + 2)))*0.8f;
				}
				else if (pDefender->ATTRIBUTE_NUM == normal)
				{
					eCriticalSkillDamage = pAttacker->ATK * 1.2f - (pDefender->DEF / (rand() % 3 + 2));
					eSkillDamage = pAttacker->ATK - (pDefender->DEF / (rand() % 2 + 2));
				}
			}
			else if (rand() % 100 >= 20 && rand() % 100 < 40)
			{
				strcpy(pSkill->SKILL_NAME, "雷鳴斬");
				pSkill->SKILL_AT_NUM == thunder;
				if (pDefender->ATTRIBUTE_NUM == fire)
				{
					eCriticalSkillDamage = (pAttacker->ATK * 1.2f - (pDefender->DEF / (rand() % 3 + 2))) * 0.8f;
					eSkillDamage = (pAttacker->ATK - (pDefender->DEF / (rand() % 2 + 2))) * 0.8f;
				}
				else if (pDefender->ATTRIBUTE_NUM == thunder)
				{
					eCriticalSkillDamage = pAttacker->ATK * 1.2f - (pDefender->DEF / (rand() % 3 + 2));
					eSkillDamage = pAttacker->ATK - (pDefender->DEF / (rand() % 2 + 2));
				}
				else if (pDefender->ATTRIBUTE_NUM == soil)
				{
					eCriticalSkillDamage = (pAttacker->ATK * 1.2f - (pDefender->DEF / (rand() % 3 + 2))) * 1.2f;
					eSkillDamage = (pAttacker->ATK - (pDefender->DEF / (rand() % 2 + 2))) * 1.2f;
				}
				else if (pDefender->ATTRIBUTE_NUM == normal)
				{
					eCriticalSkillDamage = pAttacker->ATK * 1.2f - (pDefender->DEF / (rand() % 3 + 2));
					eSkillDamage = pAttacker->ATK - (pDefender->DEF / (rand() % 2 + 2));
				}
			}
			else if (rand() % 100 >= 40 && rand() % 100 < 60)
			{
				strcpy(pSkill->SKILL_NAME, "大地斬");
				pSkill->SKILL_AT_NUM == soil;
				if (pDefender->ATTRIBUTE_NUM == fire)
				{
					eCriticalSkillDamage = (pAttacker->ATK * 1.2f - (pDefender->DEF / (rand() % 3 + 2))) * 1.2f;
					eSkillDamage = (pAttacker->ATK - (pDefender->DEF / (rand() % 2 + 2))) * 1.2f;
				}
				else if (pDefender->ATTRIBUTE_NUM == thunder)
				{
					eCriticalSkillDamage = (pAttacker->ATK * 1.2f - (pDefender->DEF / (rand() % 3 + 2))) * 0.8f;
					eSkillDamage = (pAttacker->ATK - (pDefender->DEF / (rand() % 2 + 2))) * 0.8f;
				}
				else if (pDefender->ATTRIBUTE_NUM == soil)
				{
					eCriticalSkillDamage = pAttacker->ATK * 1.2f - (pDefender->DEF / (rand() % 3 + 2));
					eSkillDamage = pAttacker->ATK - (pDefender->DEF / (rand() % 2 + 2));
				}
				else if (pDefender->ATTRIBUTE_NUM == normal)
				{
					eCriticalSkillDamage = pAttacker->ATK * 1.2f - (pDefender->DEF / (rand() % 3 + 2));
					eSkillDamage = pAttacker->ATK - (pDefender->DEF / (rand() % 2 + 2));
				}
			}
			else if (rand() % 100 >= 60 && rand() % 100 < 90)
			{
				strcpy(pSkill->SKILL_NAME, "剛撃");
				pSkill->SKILL_AT_NUM = normal;
				eCriticalSkillDamage = (pAttacker->ATK * 1.2f - (pDefender->DEF / (rand() % 3 + 2)))*1.1f;
				eSkillDamage = (pAttacker->ATK - (pDefender->DEF / (rand() % 2 + 2)))*1.1f;
			}
			else
			{
				strcpy(pSkill->SKILL_NAME, "気合ため");
				gotoxy(*pX, *pY);
				printf("%s\n", pSkill->SKILL_NAME);
				*pY = wherey();
				if (*pPhyEFrag == 0)
				{
					gotoxy(*pX, *pY);
					printf("次のターンまで攻撃力が上昇▽");
					*pY = wherey(),*pX=wherex();
					pAttacker->ATK += pAttacker->ATK / 2;
					*pPhyEFrag = 1;
				}
				*pBuff = 1;
			}
		}
		else if (pAttacker->JOBNUM == tankNum)
		{
			if (rand() % 100 < 10)
			{
				if (*pEnemyDefLimit < 3)
				{
					strcpy(pSkill->SKILL_NAME, "剛体");
					gotoxy(*pX, *pY);
					printf("%s\n", pSkill->SKILL_NAME);
					*pY = wherey();
					pSkill->SKILL_AT_NUM == normal;
					enemyStatusUp = rand() % 11 + 5;
					pAttacker->DEF += enemyStatusUp;
					gotoxy(*pX, *pY);
					printf("%sの防御力が%d上がった\n", pAttacker->NAME, enemyStatusUp);
					*pY = wherey();
					enemyStatusUp = rand() % 11 + 5;
					pAttacker->MDEF += enemyStatusUp;
					gotoxy(*pX, *pY);
					printf("%sの魔防が%d上昇▽", pAttacker->NAME, enemyStatusUp);
					*pY = wherey(),*pX=wherex();
					*pEnemyDefLimit += 1;
					*pBuff = 1;
				}
				else
				{
					gotoxy(*pX, *pY);
					printf("これ以上は意味が無さそうだ...▽");
					*pY = wherey(),*pX=wherex();
				}
			}
			else if (rand() % 100 >= 10 && rand() % 100 < 30)
			{
				if (*pEnemyLuckLimit < 3)
				{
					strcpy(pSkill->SKILL_NAME, "祈祷");
					gotoxy(*pX, *pY);
					printf("%s\n", pSkill->SKILL_NAME);
					*pY = wherey();
					pSkill->SKILL_AT_NUM == normal;
					enemyStatusUp = rand() % 11 + 5;
					pAttacker->LUCK += enemyStatusUp;
					gotoxy(*pX, *pY);
					printf("%sの運が%d上がった▽", pAttacker->NAME, enemyStatusUp);
					*pY = wherey(),*pX=wherex();
					*pEnemyLuckLimit += 1;
					*pBuff = 1;
				}
				else
				{
					gotoxy(*pX, *pY);
					printf("これ以上は意味が無さそうだ...▽");
					*pY = wherey(),*pX=wherex();
				}
			}
			else if (rand() % 100 >= 30 && rand() % 100 < 50)
			{
				strcpy(pSkill->SKILL_NAME, "火炎斬");
				pSkill->SKILL_AT_NUM == fire;
				if (pDefender->ATTRIBUTE_NUM == fire)
				{
					eCriticalSkillDamage = pAttacker->ATK * 1.2f - (pDefender->DEF / (rand() % 3 + 2));
					eSkillDamage = pAttacker->ATK - (pDefender->DEF / (rand() % 2 + 2));
				}
				else if (pDefender->ATTRIBUTE_NUM == thunder)
				{
					eCriticalSkillDamage = (pAttacker->ATK * 1.2f - (pDefender->DEF / (rand() % 3 + 2))) * 1.2f;
					eSkillDamage = (pAttacker->ATK - (pDefender->DEF / (rand() % 2 + 2))) * 1.2f;
				}
				else if (pDefender->ATTRIBUTE_NUM == soil)
				{
					eCriticalSkillDamage = (pAttacker->ATK * 1.2f - (pDefender->DEF / (rand() % 3 + 2))) * 0.8f;
					eSkillDamage = (pAttacker->ATK - (pDefender->DEF / (rand() % 2 + 2))) * 0.8f;
				}
				else if (pDefender->ATTRIBUTE_NUM == normal)
				{
					eCriticalSkillDamage = pAttacker->ATK * 1.2f - (pDefender->DEF / (rand() % 3 + 2));
					eSkillDamage = pAttacker->ATK - (pDefender->DEF / (rand() % 2 + 2));
				}
			}
			else if (rand() % 100 >= 50 && rand() % 100 < 70)
			{
				strcpy(pSkill->SKILL_NAME, "大地斬");
				pSkill->SKILL_AT_NUM == soil;
				if (pDefender->ATTRIBUTE_NUM == fire)
				{
					eCriticalSkillDamage = (pAttacker->ATK * 1.2f - (pDefender->DEF / (rand() % 3 + 2))) * 1.2f;
					eSkillDamage = (pAttacker->ATK - (pDefender->DEF / (rand() % 2 + 2))) * 1.2f;
				}
				else if (pDefender->ATTRIBUTE_NUM == thunder)
				{
					eCriticalSkillDamage = (pAttacker->ATK * 1.2f - (pDefender->DEF / (rand() % 3 + 2))) * 0.8f;
					eSkillDamage = (pAttacker->ATK - (pDefender->DEF / (rand() % 2 + 2))) * 0.8f;
				}
				else if (pDefender->ATTRIBUTE_NUM == soil)
				{
					eCriticalSkillDamage = pAttacker->ATK * 1.2f - (pDefender->DEF / (rand() % 3 + 2));
					eSkillDamage = pAttacker->ATK - (pDefender->DEF / (rand() % 2 + 2));
				}
				else if (pDefender->ATTRIBUTE_NUM == normal)
				{
					eCriticalSkillDamage = pAttacker->ATK * 1.2f - (pDefender->DEF / (rand() % 3 + 2));
					eSkillDamage = pAttacker->ATK - (pDefender->DEF / (rand() % 2 + 2));
				}
			}
			else
			{
				strcpy(pSkill->SKILL_NAME, "剛撃");
				pSkill->SKILL_AT_NUM = normal;
				eCriticalSkillDamage = (pAttacker->ATK * 1.2f - (pDefender->DEF / (rand() % 3 + 2))) * 1.1f;
				eSkillDamage = (pAttacker->ATK - (pDefender->DEF / (rand() % 2 + 2))) * 1.1f;
			}
		}
		else if (pAttacker->JOBNUM == wizardNum)
		{
			if (rand() % 100 < 20)
			{
				strcpy(pSkill->SKILL_NAME, "火炎");
				pSkill->SKILL_AT_NUM == fire;
				if (pDefender->ATTRIBUTE_NUM == fire)
				{
					eCriticalSkillDamage = (pAttacker->MATK * 1.2f - (pDefender->MDEF / (rand() % 3 + 2)));
					eSkillDamage = (pAttacker->MATK - (pDefender->MDEF / (rand() % 2 + 2)));
				}
				else if (pDefender->ATTRIBUTE_NUM == thunder)
				{
					eCriticalSkillDamage = (pAttacker->MATK * 1.2f - (pDefender->MDEF / (rand() % 3 + 2)))*1.2f;
					eSkillDamage = (pAttacker->MATK - (pDefender->MDEF / (rand() % 2 + 2)))*1.2f;
				}
				else if (pDefender->ATTRIBUTE_NUM == soil)
				{
					eCriticalSkillDamage = (pAttacker->MATK * 1.2f - (pDefender->MDEF / (rand() % 3 + 2)))*0.8f;
					eSkillDamage = (pAttacker->MATK - (pDefender->MDEF / (rand() % 2 + 2)))*0.8f;
				}
				if (pDefender->ATTRIBUTE_NUM == normal)
				{
					eCriticalSkillDamage = (pAttacker->MATK * 1.2f - (pDefender->MDEF / (rand() % 3 + 2)));
					eSkillDamage = (pAttacker->MATK - (pDefender->MDEF / (rand() % 2 + 2)));
				}
			}
			else if (rand() % 100 >= 20 && rand() % 100 < 40)
			{
				strcpy(pSkill->SKILL_NAME, "雷撃");
				pSkill->SKILL_AT_NUM == thunder;
				if (pDefender->ATTRIBUTE_NUM == fire)
				{
					eCriticalSkillDamage = (pAttacker->MATK * 1.2f - (pDefender->MDEF / (rand() % 3 + 2)))*0.8f;
					eSkillDamage = (pAttacker->MATK - (pDefender->MDEF / (rand() % 2 + 2)))*0.8f;
				}
				else if (pDefender->ATTRIBUTE_NUM == thunder)
				{
					eCriticalSkillDamage = (pAttacker->MATK * 1.2f - (pDefender->MDEF / (rand() % 3 + 2)));
					eSkillDamage = (pAttacker->MATK - (pDefender->MDEF / (rand() % 2 + 2)));
				}
				else if (pDefender->ATTRIBUTE_NUM == soil)
				{
					eCriticalSkillDamage = (pAttacker->MATK * 1.2f - (pDefender->MDEF / (rand() % 3 + 2))) * 1.2f;
					eSkillDamage = (pAttacker->MATK - (pDefender->MDEF / (rand() % 2 + 2))) * 1.2f;
				}
				if (pDefender->ATTRIBUTE_NUM == normal)
				{
					eCriticalSkillDamage = (pAttacker->MATK * 1.2f - (pDefender->MDEF / (rand() % 3 + 2)));
					eSkillDamage = (pAttacker->MATK - (pDefender->MDEF / (rand() % 2 + 2)));
				}
			}
			else if (rand() % 100 >= 40 && rand() % 100 < 60)
			{
				strcpy(pSkill->SKILL_NAME, "落石");
				pSkill->SKILL_AT_NUM == soil;
				if (pDefender->ATTRIBUTE_NUM == fire)
				{
					eCriticalSkillDamage = (pAttacker->MATK * 1.2f - (pDefender->MDEF / (rand() % 3 + 2))) * 1.2f;
					eSkillDamage = (pAttacker->MATK - (pDefender->MDEF / (rand() % 2 + 2))) * 1.2f;
				}
				else if (pDefender->ATTRIBUTE_NUM == thunder)
				{
					eCriticalSkillDamage = (pAttacker->MATK * 1.2f - (pDefender->MDEF / (rand() % 3 + 2)))*0.8f;
					eSkillDamage = (pAttacker->MATK - (pDefender->MDEF / (rand() % 2 + 2)))*0.8f;
				}
				else if (pDefender->ATTRIBUTE_NUM == soil)
				{
					eCriticalSkillDamage = (pAttacker->MATK * 1.2f - (pDefender->MDEF / (rand() % 3 + 2)));
					eSkillDamage = (pAttacker->MATK - (pDefender->MDEF / (rand() % 2 + 2)));
				}
				if (pDefender->ATTRIBUTE_NUM == normal)
				{
					eCriticalSkillDamage = (pAttacker->MATK * 1.2f - (pDefender->MDEF / (rand() % 3 + 2)));
					eSkillDamage = (pAttacker->MATK - (pDefender->MDEF / (rand() % 2 + 2)));
				}
			}
			else if (rand() % 100 >= 60 && rand() % 100 < 90)
			{
				strcpy(pSkill->SKILL_NAME, "星降り");
				pSkill->SKILL_AT_NUM == normal;
				if (rand() % (pAttacker->LUCK / 3) > rand() % (pAttacker->LUCK))
				{
					eCriticalSkillDamage = (pAttacker->MATK * 1.2f - (pDefender->MDEF / (rand() % 3 + 2)))*1.5;
					eSkillDamage = (pAttacker->MATK - (pDefender->MDEF / (rand() % 2 + 2)))*1.5;
				}
				else
				{
					gotoxy(*pX, *pY);
					printf("何も起こらなかった▽");
					*pY = wherey(),*pX=wherex();
					*pBuff = 1;
				}
			}
			else
			{
				if (*pEnemyLuckLimit < 3)
				{
					strcpy(pSkill->SKILL_NAME, "祈祷");
					gotoxy(*pX, *pY);
					printf("%s\n", pSkill->SKILL_NAME);
					*pY = wherey();
					pSkill->SKILL_AT_NUM == normal;
					enemyStatusUp = rand() % 11 + 5;
					pAttacker->LUCK += enemyStatusUp;
					gotoxy(*pX, *pY);
					printf("%sの運が%d上がった▽", pAttacker->NAME, enemyStatusUp);
					*pY = wherey(),*pX=wherex();
					*pEnemyLuckLimit += 1;
					*pBuff = 1;
				}
			}
		}
		else if (pAttacker->JOBNUM == assassinNum)
		{
			if (rand() % 100 < 20)
			{
				strcpy(pSkill->SKILL_NAME, "火炎斬");
				pSkill->SKILL_AT_NUM == fire;
				if (pDefender->ATTRIBUTE_NUM == fire)
				{
					eCriticalSkillDamage = pAttacker->ATK * 1.2f - (pDefender->DEF / (rand() % 3 + 2));
					eSkillDamage = pAttacker->ATK - (pDefender->DEF / (rand() % 2 + 2));
				}
				else if (pDefender->ATTRIBUTE_NUM == thunder)
				{
					eCriticalSkillDamage = (pAttacker->ATK * 1.2f - (pDefender->DEF / (rand() % 3 + 2))) * 1.2f;
					eSkillDamage = (pAttacker->ATK - (pDefender->DEF / (rand() % 2 + 2))) * 1.2f;
				}
				else if (pDefender->ATTRIBUTE_NUM == soil)
				{
					eCriticalSkillDamage = (pAttacker->ATK * 1.2f - (pDefender->DEF / (rand() % 3 + 2))) * 0.8f;
					eSkillDamage = (pAttacker->ATK - (pDefender->DEF / (rand() % 2 + 2))) * 0.8f;
				}
				else if (pDefender->ATTRIBUTE_NUM == normal)
				{
					eCriticalSkillDamage = pAttacker->ATK * 1.2f - (pDefender->DEF / (rand() % 3 + 2));
					eSkillDamage = pAttacker->ATK - (pDefender->DEF / (rand() % 2 + 2));
				}
			}
			else if (rand() % 100 >= 20 && rand() % 100 < 40)
			{
				strcpy(pSkill->SKILL_NAME, "雷鳴斬");
				pSkill->SKILL_AT_NUM == thunder;
				if (pDefender->ATTRIBUTE_NUM == fire)
				{
					eCriticalSkillDamage = pAttacker->ATK * 1.2f - (pDefender->DEF / (rand() % 3 + 2))*0.8f;
					eSkillDamage = pAttacker->ATK - (pDefender->DEF / (rand() % 2 + 2))*0.8f;
				}
				else if (pDefender->ATTRIBUTE_NUM == thunder)
				{
					eCriticalSkillDamage = (pAttacker->ATK * 1.2f - (pDefender->DEF / (rand() % 3 + 2)));
					eSkillDamage = (pAttacker->ATK - (pDefender->DEF / (rand() % 2 + 2)));
				}
				else if (pDefender->ATTRIBUTE_NUM == soil)
				{
					eCriticalSkillDamage = (pAttacker->ATK * 1.2f - (pDefender->DEF / (rand() % 3 + 2))) * 1.2f;
					eSkillDamage = (pAttacker->ATK - (pDefender->DEF / (rand() % 2 + 2))) * 1.2f;
				}
				else if (pDefender->ATTRIBUTE_NUM == normal)
				{
					eCriticalSkillDamage = pAttacker->ATK * 1.2f - (pDefender->DEF / (rand() % 3 + 2));
					eSkillDamage = pAttacker->ATK - (pDefender->DEF / (rand() % 2 + 2));
				}
			}
			else if (rand() % 100 >= 40 && rand() % 100 < 60)
			{
				strcpy(pSkill->SKILL_NAME, "落石");
				pSkill->SKILL_AT_NUM == soil;
				if (pDefender->ATTRIBUTE_NUM == fire)
				{
					eCriticalSkillDamage = (pAttacker->MATK * 1.2f - (pDefender->MDEF / (rand() % 3 + 2))) * 1.2f;
					eSkillDamage = (pAttacker->MATK - (pDefender->MDEF / (rand() % 2 + 2))) * 1.2f;
				}
				else if (pDefender->ATTRIBUTE_NUM == thunder)
				{
					eCriticalSkillDamage = (pAttacker->MATK * 1.2f - (pDefender->MDEF / (rand() % 3 + 2))) * 0.8f;
					eSkillDamage = (pAttacker->MATK - (pDefender->MDEF / (rand() % 2 + 2))) * 0.8f;
				}
				else if (pDefender->ATTRIBUTE_NUM == soil)
				{
					eCriticalSkillDamage = (pAttacker->MATK * 1.2f - (pDefender->MDEF / (rand() % 3 + 2)));
					eSkillDamage = (pAttacker->MATK - (pDefender->MDEF / (rand() % 2 + 2)));
				}
				if (pDefender->ATTRIBUTE_NUM == normal)
				{
					eCriticalSkillDamage = (pAttacker->MATK * 1.2f - (pDefender->MDEF / (rand() % 3 + 2)));
					eSkillDamage = (pAttacker->MATK - (pDefender->MDEF / (rand() % 2 + 2)));
				}
			}
			else if (rand() % 100 >= 60 && rand() % 100 < 80)
			{
				strcpy(pSkill->SKILL_NAME, "雷撃");
				pSkill->SKILL_AT_NUM == thunder;
				if (pDefender->ATTRIBUTE_NUM == fire)
				{
					eCriticalSkillDamage = (pAttacker->MATK * 1.2f - (pDefender->MDEF / (rand() % 3 + 2))) * 0.8f;
					eSkillDamage = (pAttacker->MATK - (pDefender->MDEF / (rand() % 2 + 2))) * 0.8f;
				}
				else if (pDefender->ATTRIBUTE_NUM == thunder)
				{
					eCriticalSkillDamage = (pAttacker->MATK * 1.2f - (pDefender->MDEF / (rand() % 3 + 2)));
					eSkillDamage = (pAttacker->MATK - (pDefender->MDEF / (rand() % 2 + 2)));
				}
				else if (pDefender->ATTRIBUTE_NUM == soil)
				{
					eCriticalSkillDamage = (pAttacker->MATK * 1.2f - (pDefender->MDEF / (rand() % 3 + 2))) * 1.2f;
					eSkillDamage = (pAttacker->MATK - (pDefender->MDEF / (rand() % 2 + 2))) * 1.2f;
				}
				if (pDefender->ATTRIBUTE_NUM == normal)
				{
					eCriticalSkillDamage = (pAttacker->MATK * 1.2f - (pDefender->MDEF / (rand() % 3 + 2)));
					eSkillDamage = (pAttacker->MATK - (pDefender->MDEF / (rand() % 2 + 2)));
				}
			}
			else
			{
				strcpy(pSkill->SKILL_NAME, "辻斬り");
				pSkill->SKILL_AT_NUM == normal;
				eCriticalSkillDamage = pAttacker->ATK * 1.2f - (pDefender->DEF / (rand() % 3 + 2)) + pAttacker->SPD / 2;
				eSkillDamage = pAttacker->ATK - (pDefender->DEF / (rand() % 2 + 2)) + pAttacker->SPD / 2;
			}
		}
	}
	else if (pAttacker->IDEN == bossIdenNum)
	{
		if (pAttacker->BOSSIDEN == αNum)
		{
			if (rand() % 100 < 20)
			{
				strcpy(pSkill->SKILL_NAME, "火炎斬");
				pSkill->SKILL_AT_NUM == fire;
				if (pDefender->ATTRIBUTE_NUM == fire)
				{
					eCriticalSkillDamage = pAttacker->ATK * 1.2f - (pDefender->DEF / (rand() % 3 + 2));
					eSkillDamage = pAttacker->ATK - (pDefender->DEF / (rand() % 2 + 2));
				}
				else if (pDefender->ATTRIBUTE_NUM == thunder)
				{
					eCriticalSkillDamage = (pAttacker->ATK * 1.2f - (pDefender->DEF / (rand() % 3 + 2))) * 1.2f;
					eSkillDamage = (pAttacker->ATK - (pDefender->DEF / (rand() % 2 + 2))) * 1.2f;
				}
				else if (pDefender->ATTRIBUTE_NUM == soil)
				{
					eCriticalSkillDamage = (pAttacker->ATK * 1.2f - (pDefender->DEF / (rand() % 3 + 2))) * 0.8f;
					eSkillDamage = (pAttacker->ATK - (pDefender->DEF / (rand() % 2 + 2))) * 0.8f;
				}
				else if (pDefender->ATTRIBUTE_NUM == normal)
				{
					eCriticalSkillDamage = pAttacker->ATK * 1.2f - (pDefender->DEF / (rand() % 3 + 2));
					eSkillDamage = pAttacker->ATK - (pDefender->DEF / (rand() % 2 + 2));
				}
			}
			else if (rand() % 100 >= 20 && rand() % 100 < 40)
			{
				strcpy(pSkill->SKILL_NAME, "火炎");
				pSkill->SKILL_AT_NUM == fire;
				if (pDefender->ATTRIBUTE_NUM == fire)
				{
					eCriticalSkillDamage = (pAttacker->MATK * 1.2f - (pDefender->MDEF / (rand() % 3 + 2)));
					eSkillDamage = (pAttacker->MATK - (pDefender->MDEF / (rand() % 2 + 2)));
				}
				else if (pDefender->ATTRIBUTE_NUM == thunder)
				{
					eCriticalSkillDamage = (pAttacker->MATK * 1.2f - (pDefender->MDEF / (rand() % 3 + 2))) * 1.2f;
					eSkillDamage = (pAttacker->MATK - (pDefender->MDEF / (rand() % 2 + 2))) * 1.2f;
				}
				else if (pDefender->ATTRIBUTE_NUM == soil)
				{
					eCriticalSkillDamage = (pAttacker->MATK * 1.2f - (pDefender->MDEF / (rand() % 3 + 2))) * 0.8f;
					eSkillDamage = (pAttacker->MATK - (pDefender->MDEF / (rand() % 2 + 2))) * 0.8f;
				}
				if (pDefender->ATTRIBUTE_NUM == normal)
				{
					eCriticalSkillDamage = (pAttacker->MATK * 1.2f - (pDefender->MDEF / (rand() % 3 + 2)));
					eSkillDamage = (pAttacker->MATK - (pDefender->MDEF / (rand() % 2 + 2)));
				}
			}
			else if (rand() % 100 >= 40 && rand() % 100 < 70)
			{
				strcpy(pSkill->SKILL_NAME, "剛撃");
				pSkill->SKILL_AT_NUM == normal;
				eCriticalSkillDamage = pAttacker->ATK * 1.2f - (pDefender->DEF / (rand() % 3 + 2))*1.1f;
				eSkillDamage = pAttacker->ATK - (pDefender->DEF / (rand() % 2 + 2))*1.1f;
			}
			else if (rand() % 100 >= 70 && rand() %100 < 90)
			{
				strcpy(pSkill->SKILL_NAME, "剛体");
				gotoxy(*pX, *pY);
				printf("%s\n", pSkill->SKILL_NAME);
				*pY = wherey();
				pSkill->SKILL_AT_NUM == normal;
				enemyStatusUp = rand() % 11 + 5;
				pAttacker->DEF += enemyStatusUp;
				gotoxy(*pX, *pY);
				printf("%sの防御力が%d上がった\n", pAttacker->NAME, enemyStatusUp);
				*pY = wherey();
				enemyStatusUp = rand() % 11 + 5;
				pAttacker->MDEF += enemyStatusUp;
				gotoxy(*pX, *pY);
				printf("%sの魔防が%d上昇▽", pAttacker->NAME, enemyStatusUp);
				*pY = wherey(),*pX=wherex();
				gotoxy(*pX, *pY);
				*pEnemyDefLimit += 1;
				*pBuff = 1;
			}
			else
			{
				strcpy(pSkill->SKILL_NAME, "廻転");
				pSkill->SKILL_AT_NUM == normal;
				textcolor(MAGENTA);
				gotoxy(*pX, *pY);
				printf("『シンキイッテン』\n");
				*pY = wherey();
				textcolor(WHITE);
				gotoxy(*pX, *pY);
				printf("%s\n", pSkill->SKILL_NAME);
				*pY = wherey();
				gotoxy(*pX, *pY);
				printf("攻撃力と防御力が反転した▽");
				*pY = wherey(),*pX=wherex();
				gotoxy(*pX, *pY);
				change = pAttacker->ATK;
				pAttacker->ATK = pAttacker->DEF;
				pAttacker->DEF = change;
				*pBuff = 1;
			}
		}
		else if (pAttacker->BOSSIDEN == βNum)
		{
			if (rand() % 100 < 20)
			{
				strcpy(pSkill->SKILL_NAME, "雷撃");
				pSkill->SKILL_AT_NUM == thunder;
				if (pDefender->ATTRIBUTE_NUM == fire)
				{
					eCriticalSkillDamage = (pAttacker->MATK * 1.2f - (pDefender->MDEF / (rand() % 3 + 2)))*0.8f;
					eSkillDamage = (pAttacker->MATK - (pDefender->MDEF / (rand() % 2 + 2)))*0.8f;
				}
				else if (pDefender->ATTRIBUTE_NUM == thunder)
				{
					eCriticalSkillDamage = (pAttacker->MATK * 1.2f - (pDefender->MDEF / (rand() % 3 + 2)));
					eSkillDamage = (pAttacker->MATK - (pDefender->MDEF / (rand() % 2 + 2)));
				}
				else if (pDefender->ATTRIBUTE_NUM == soil)
				{
					eCriticalSkillDamage = (pAttacker->MATK * 1.2f - (pDefender->MDEF / (rand() % 3 + 2))) * 1.2f;
					eSkillDamage = (pAttacker->MATK - (pDefender->MDEF / (rand() % 2 + 2))) * 1.2f;
				}
				if (pDefender->ATTRIBUTE_NUM == normal)
				{
					eCriticalSkillDamage = (pAttacker->MATK * 1.2f - (pDefender->MDEF / (rand() % 3 + 2)));
					eSkillDamage = (pAttacker->MATK - (pDefender->MDEF / (rand() % 2 + 2)));
				}
			}
			else if (rand() % 100 >= 20 && rand() % 100 < 40)
			{
				strcpy(pSkill->SKILL_NAME, "雷鳴斬");
				pSkill->SKILL_AT_NUM == thunder;
				if (pDefender->ATTRIBUTE_NUM == fire)
				{
					eCriticalSkillDamage = pAttacker->ATK * 1.2f - (pDefender->DEF / (rand() % 3 + 2))*0.8f;
					eSkillDamage = pAttacker->ATK - (pDefender->DEF / (rand() % 2 + 2))*0.8f;
				}
				else if (pDefender->ATTRIBUTE_NUM == thunder)
				{
					eCriticalSkillDamage = (pAttacker->ATK * 1.2f - (pDefender->DEF / (rand() % 3 + 2)));
					eSkillDamage = (pAttacker->ATK - (pDefender->DEF / (rand() % 2 + 2)));
				}
				else if (pDefender->ATTRIBUTE_NUM == soil)
				{
					eCriticalSkillDamage = (pAttacker->ATK * 1.2f - (pDefender->DEF / (rand() % 3 + 2))) * 1.2f;
					eSkillDamage = (pAttacker->ATK - (pDefender->DEF / (rand() % 2 + 2))) * 1.2f;
				}
				else if (pDefender->ATTRIBUTE_NUM == normal)
				{
					eCriticalSkillDamage = pAttacker->ATK * 1.2f - (pDefender->DEF / (rand() % 3 + 2));
					eSkillDamage = pAttacker->ATK - (pDefender->DEF / (rand() % 2 + 2));
				}
			}
			else if (rand() % 100 >= 40 && rand() % 100 < 60)
			{
				strcpy(pSkill->SKILL_NAME, "辻斬り");
				pSkill->SKILL_AT_NUM == normal;
				eCriticalSkillDamage = pAttacker->ATK * 1.2f - (pDefender->DEF / (rand() % 3 + 2)) + pAttacker->SPD / 2;
				eSkillDamage = pAttacker->ATK - (pDefender->DEF / (rand() % 2 + 2)) + pAttacker->SPD / 2;
			}
			else if (rand() % 100 >= 60 && rand() % 100 < 90)
			{
				strcpy(pSkill->SKILL_NAME, "気合ため");
				gotoxy(*pX, *pY);
				printf("%s\n", pSkill->SKILL_NAME);
				*pY = wherey();
				if (*pPhyEFrag == 0)
				{
					gotoxy(*pX, *pY);
					printf("次のターンまで攻撃力が上昇\n");
					*pY = wherey();
					gotoxy(*pX, *pY);
					pAttacker->ATK += pAttacker->ATK / 2;
					*pPhyEFrag = 1;
				}
				*pBuff = 1;
			}
			else
			{
				strcpy(pSkill->SKILL_NAME, "撃滅");
				pSkill->SKILL_AT_NUM == normal;
				textcolor(MAGENTA);
				gotoxy(*pX, *pY);
				printf("『...』\n");
				*pY = wherey();
				textcolor(WHITE);
				gotoxy(*pX, *pY);
				eCriticalSkillDamage = pDefender->LIFE / 2;
				eSkillDamage = pDefender->LIFE / 2;
			}
		}
		else if (pAttacker->BOSSIDEN == εNum)
		{
			if (rand() % 100 < 30)
			{
				strcpy(pSkill->SKILL_NAME, "祈祷");
				gotoxy(*pX, *pY);
				printf("%s\n", pSkill->SKILL_NAME);
				*pY = wherey();
				pSkill->SKILL_AT_NUM == normal;
				enemyStatusUp = rand() % 11 + 5;
				pAttacker->LUCK += enemyStatusUp;
				gotoxy(*pX, *pY);
				printf("%sの運が%d上がった▽", pAttacker->NAME, enemyStatusUp);
				*pY = wherey(),*pX=wherex();
				gotoxy(*pX, *pY);
				*pBuff = 1;
			}
			else if (rand() % 100 >= 20 && rand() % 100 < 60)
			{
				strcpy(pSkill->SKILL_NAME, "落石");
				pSkill->SKILL_AT_NUM == soil;
				if (pDefender->ATTRIBUTE_NUM == fire)
				{
					eCriticalSkillDamage = (pAttacker->MATK * 1.2f - (pDefender->MDEF / (rand() % 3 + 2))) * 1.2f;
					eSkillDamage = (pAttacker->MATK - (pDefender->MDEF / (rand() % 2 + 2))) * 1.2f;
				}
				else if (pDefender->ATTRIBUTE_NUM == thunder)
				{
					eCriticalSkillDamage = (pAttacker->MATK * 1.2f - (pDefender->MDEF / (rand() % 3 + 2))) * 0.8f;
					eSkillDamage = (pAttacker->MATK - (pDefender->MDEF / (rand() % 2 + 2))) * 0.8f;
				}
				else if (pDefender->ATTRIBUTE_NUM == soil)
				{
					eCriticalSkillDamage = (pAttacker->MATK * 1.2f - (pDefender->MDEF / (rand() % 3 + 2)));
					eSkillDamage = (pAttacker->MATK - (pDefender->MDEF / (rand() % 2 + 2)));
				}
				if (pDefender->ATTRIBUTE_NUM == normal)
				{
					eCriticalSkillDamage = (pAttacker->MATK * 1.2f - (pDefender->MDEF / (rand() % 3 + 2)));
					eSkillDamage = (pAttacker->MATK - (pDefender->MDEF / (rand() % 2 + 2)));
				}
			}
			else if (rand() % 100 >= 60 && rand() % 100 < 70)
			{
				strcpy(pSkill->SKILL_NAME, "魔力ため");
				gotoxy(*pX, *pY);
				printf("%s\n", pSkill->SKILL_NAME);
				*pY = wherey();
				if (*pMagEFrag == 0)
				{
					gotoxy(*pX, *pY);
					printf("次のターンまで魔力が上昇▽");
					*pY = wherey(),*pX=wherex();
					gotoxy(*pX, *pY);
					pAttacker->ATK += pAttacker->ATK / 2;
					*pMagEFrag = 1;
				}
				*pBuff = 1;
			}
			else if (rand() % 100 >= 70 && rand() % 100 < 90)
			{
				strcpy(pSkill->SKILL_NAME, "星降り");
				pSkill->SKILL_AT_NUM == normal;
				if (rand() % (pAttacker->LUCK / 3) > rand() % (pAttacker->LUCK))
				{
					eCriticalSkillDamage = (pAttacker->MATK * 1.2f - (pDefender->MDEF / (rand() % 3 + 2)))*1.5;
					eSkillDamage = (pAttacker->MATK - (pDefender->MDEF / (rand() % 2 + 2))) * 1.5;
				}
				else
				{
					gotoxy(*pX, *pY);
					printf("何も起こらなかった▽");
					*pY = wherey(),*pX=wherex();
					gotoxy(*pX, *pY);
					*pBuff = 1;
				}
			}
			else if (rand() % 100 >= 90 && rand() % 100 < 100)
			{
				strcpy(pSkill->SKILL_NAME, "天啓");
				textcolor(MAGENTA);
				gotoxy(*pX, *pY);
				printf("『カミノメグミ』\n");
				*pY = wherey();
				textcolor(WHITE);
				gotoxy(*pX, *pY);
				printf("%s\n", pSkill->SKILL_NAME);
				*pY = wherey();
				gotoxy(*pX, *pY);
				printf("魔力が上昇した▽");
				*pY = wherey(),*pX=wherex();
				gotoxy(*pX, *pY);
				pSkill->SKILL_AT_NUM == normal;
				pAttacker->MATK += pAttacker->MATK * 0.3;
				*pBuff = 1;
			}
		}
		else if (pAttacker->BOSSIDEN == ΩNum)
		{
			if (rand() % 100 > 30)
			{
				strcpy(pSkill->SKILL_NAME, "剛撃");
				pSkill->SKILL_AT_NUM = normal;
				eCriticalSkillDamage = pAttacker->ATK * 1.2f - (pDefender->DEF / (rand() % 3 + 2))*1.1f;
				eSkillDamage = pAttacker->ATK - (pDefender->DEF / (rand() % 2 + 2))*1.1f;
			}
			else if (rand() % 100 >= 30 && rand() % 100 < 60)
			{
				strcpy(pSkill->SKILL_NAME, "辻斬り");
				pSkill->SKILL_AT_NUM == normal;
				eCriticalSkillDamage = pAttacker->ATK * 1.2f - (pDefender->DEF / (rand() % 3 + 2)) + pAttacker->SPD / 2;
				eSkillDamage = pAttacker->ATK - (pDefender->DEF / (rand() % 2 + 2)) + pAttacker->SPD / 2;
			}
			else if (rand() % 100 >= 60 && rand() % 100 < 80)
			{
				strcpy(pSkill->SKILL_NAME, "気合ため");
				gotoxy(*pX, *pY);
				printf("%s\n", pSkill->SKILL_NAME);
				*pY = wherey();
				if (*pPhyEFrag == 0)
				{
					gotoxy(*pX, *pY);
					printf("次のターンまで攻撃力が上昇▽");
					*pY = wherey(),*pX=wherex();
					gotoxy(*pX, *pY);
					pAttacker->ATK += pAttacker->ATK / 2;;
					*pPhyEFrag = 1;
				}
				*pBuff = 1;
			}
			else if (rand() % 100 >= 80 && rand() % 100 < 90)
			{
				strcpy(pSkill->SKILL_NAME, "原初");
				pSkill->SKILL_AT_NUM == normal;
				textcolor(MAGENTA);
				gotoxy(*pX, *pY);
				printf("『ハジマリ』\n");
				*pY = wherey();
				textcolor(WHITE);
				gotoxy(*pX, *pY);
				printf("%s\n", pSkill->SKILL_NAME);
				*pY = wherey();
				enemyStatusUp = rand() % 11 + 5;
				pAttacker->ATK += enemyStatusUp;
				pAttacker->DEF += enemyStatusUp;
				pAttacker->MATK += enemyStatusUp;
				pAttacker->MDEF += enemyStatusUp;
				pAttacker->SPD += enemyStatusUp;
				gotoxy(*pX, *pY);
				printf("%sのが全能力が%d上がった▽", pAttacker->NAME, enemyStatusUp);
				*pY = wherey(),*pX=wherex();
				gotoxy(*pX, *pY);
				*pBuff = 1;
				bossCount = 1;
			}
			else if (rand() % 100 >= 90 && rand() % 100 < 100)
			{
				if (bossCount >= 1 && end > rand() % 100)
				{
					strcpy(pSkill->SKILL_NAME, "終焉");
					pSkill->SKILL_AT_NUM == normal;
					textcolor(MAGENTA);
					gotoxy(*pX, *pY);
					printf("オワリ▽");
					*pY = wherey(),*pX=wherex();
					textcolor(WHITE);
					gotoxy(*pX, *pY);
					eCriticalSkillDamage = pDefender->LIFE;
					eSkillDamage = pDefender->LIFE;
				}
				else
				{
					gotoxy(*pX, *pY);
					printf("遠くを見つめている...▽");
					*pY = wherey(),*pX=wherex();
					gotoxy(*pX, *pY);
					end += 1;
					*pBuff = 1;
				}
			}
		}
	}
	if (rand() % (pAttacker->LUCK / 3) > rand() % 100)
	{
		*pEnemyDamage = eCriticalSkillDamage;
		*pCritFrag = 1;
	}
	else
	{
		*pEnemyDamage = eSkillDamage;
		*pCritFrag = 0;
	}
}
//=============================
// スキル表示
//=============================
void viewSkill(SKILL_STUCK* pSkill, int* pX, int* pY)
{
	for (int i = 0; i < MAX_RETENTION_SKILL;i++)
	{
		if ((pSkill + i)->SKILL_NAME[0] != '\0')
		{
			gotoxy(*pX, *pY);
			printf("スキルの書%d【スキル:%s 性質%s 消費SP%d】\n\n", i + 1, (pSkill + i)->SKILL_NAME, (pSkill + i)->SKILL_ATTRIBUTE, (pSkill + i)->SKILL_DEL);
			*pY = wherey();
		}
		else
		{
			gotoxy(*pX, *pY);
			printf("【～NO DATA～】\n\n");
			*pY = wherey();
		}
	}
	gotoxy(*pX, *pY);
	printf("*(一度忘れたスキル、覚えなかったスキルは\n");
	*pY = wherey();
	gotoxy(*pX, *pY);
	printf("　今回の探索で再び覚えることは出来ません！)\n");
	*pY = wherey();
	*pY = *pY + 1;
}
//=============================
// アイテム
//=============================
void object(ITEM_STUCK* pItem, STATUS* pPlayer, int* pExSel, int* pX, int* pY)
{
	*pY = 5;
	ITEM_STUCK preItem = {};
	int sel = 0;
	//装備品のランダム生成//
	srand((unsigned int)time(NULL));
	if (rand() % 100 < 20)
	{
		strcpy(preItem.ITEM_NAME, "剣");
		preItem.ITEM_LIFE = rand() % 5 + (rand() % (pPlayer + *pExSel)->LEVEL) * (rand() % 2 + 1);
		preItem.ITEM_ATK = rand() % 5 + (rand() % (pPlayer + *pExSel)->LEVEL) * (rand() % 2 + 1);
		preItem.ITEM_DEF = rand() % 5 + (rand() % (pPlayer + *pExSel)->LEVEL);
		preItem.ITEM_MATK = rand() % 5 + (rand() % (pPlayer + *pExSel)->LEVEL) * (rand() % 2 + 1);
		preItem.ITEM_MDEF = rand() % 5 + (rand() % (pPlayer + *pExSel)->LEVEL);
		preItem.ITEM_SPD = rand() % 5 + (rand() % (pPlayer + *pExSel)->LEVEL);
		preItem.ITEM_LUCK = rand() % 6;
	}
	else if (rand() % 100 >= 20 && rand() % 100 < 40)
	{
		strcpy(preItem.ITEM_NAME, "盾");
		preItem.ITEM_LIFE = rand() % 5 + (rand() % (pPlayer + *pExSel)->LEVEL) * (rand() % 2 + 1);
		preItem.ITEM_ATK = rand() % 5 + (rand() % (pPlayer + *pExSel)->LEVEL);
		preItem.ITEM_DEF = rand() % 5 + (rand() % (pPlayer + *pExSel)->LEVEL) * (rand() % 2 + 1);
		preItem.ITEM_MATK = rand() % 5 + (rand() % (pPlayer + *pExSel)->LEVEL);
		preItem.ITEM_MDEF = rand() % 5 + (rand() % (pPlayer + *pExSel)->LEVEL) * (rand() % 2 + 1);
		preItem.ITEM_SPD = rand() % 5 + (rand() % (pPlayer + *pExSel)->LEVEL);
		preItem.ITEM_LUCK = rand() % 6;
	}
	else if (rand() % 100 >= 40 && rand() % 100 < 60)
	{
		strcpy(preItem.ITEM_NAME, "杖");
		preItem.ITEM_LIFE = rand() % 5 + (rand() % (pPlayer + *pExSel)->LEVEL);
		preItem.ITEM_ATK = rand() % 5 + (rand() % (pPlayer + *pExSel)->LEVEL);
		preItem.ITEM_DEF = rand() % 5 + (rand() % (pPlayer + *pExSel)->LEVEL);
		preItem.ITEM_MATK = rand() % 5 + (rand() % (pPlayer + *pExSel)->LEVEL) * (rand() % 2 + 1);
		preItem.ITEM_MDEF = rand() % 5 + (rand() % (pPlayer + *pExSel)->LEVEL) * (rand() % 2 + 1);
		preItem.ITEM_SPD = rand() % 5 + (rand() % (pPlayer + *pExSel)->LEVEL);
		preItem.ITEM_LUCK = rand() % 6 * (rand() % 2 + 1);
	}
	else if (rand() % 100 >= 60 && rand() % 100 < 80)
	{
		strcpy(preItem.ITEM_NAME, "刺突剣");
		preItem.ITEM_LIFE = rand() % 5 + (rand() % (pPlayer + *pExSel)->LEVEL);
		preItem.ITEM_ATK = rand() % 5 + (rand() % (pPlayer + *pExSel)->LEVEL) * (rand() % 2 + 1);
		preItem.ITEM_DEF = rand() % 5 + (rand() % (pPlayer + *pExSel)->LEVEL);
		preItem.ITEM_MATK = rand() % 5 + (rand() % (pPlayer + *pExSel)->LEVEL) * (rand() % 2 + 1);
		preItem.ITEM_MDEF = rand() % 5 + (rand() % (pPlayer + *pExSel)->LEVEL);
		preItem.ITEM_SPD = rand() % 5 + (rand() % (pPlayer + *pExSel)->LEVEL) * (rand() % 2 + 1);
		preItem.ITEM_LUCK = rand() % 6;
	}
	else if (rand() % 100 >= 80 && rand() % 100 < 85)
	{
		strcpy(preItem.ITEM_NAME, "叢雲剣");
		preItem.ITEM_LIFE = rand() % 5 + (rand() % (pPlayer + *pExSel)->LEVEL) * (rand() % 2 + 1);
		preItem.ITEM_ATK = rand() % 5 + (rand() % (pPlayer + *pExSel)->LEVEL) * (rand() % 3 + 1);
		preItem.ITEM_DEF = rand() % 5 + (rand() % (pPlayer + *pExSel)->LEVEL);
		preItem.ITEM_MATK = rand() % 5 + (rand() % (pPlayer + *pExSel)->LEVEL) * (rand() % 3 + 1);
		preItem.ITEM_MDEF = rand() % 5 + (rand() % (pPlayer + *pExSel)->LEVEL);
		preItem.ITEM_SPD = rand() % 5 + (rand() % (pPlayer + *pExSel)->LEVEL) * (rand() % 2 + 1);
		preItem.ITEM_LUCK = rand() % 6 * (rand() % 3 + 1);
	}
	else if (rand() % 100 >= 85 && rand() % 100 < 90)
	{
		strcpy(preItem.ITEM_NAME, "八咫鏡");
		preItem.ITEM_LIFE = rand() % 5 + (rand() % (pPlayer + *pExSel)->LEVEL) * (rand() % 2 + 1);
		preItem.ITEM_ATK = rand() % 5 + (rand() % (pPlayer + *pExSel)->LEVEL);
		preItem.ITEM_DEF = rand() % 5 + (rand() % (pPlayer + *pExSel)->LEVEL) * (rand() % 3 + 1);
		preItem.ITEM_MATK = rand() % 5 + (rand() % (pPlayer + *pExSel)->LEVEL);
		preItem.ITEM_MDEF = rand() % 5 + (rand() % (pPlayer + *pExSel)->LEVEL) * (rand() % 3 + 1);
		preItem.ITEM_SPD = rand() % 5 + (rand() % (pPlayer + *pExSel)->LEVEL) * (rand() % 2 + 1);
		preItem.ITEM_LUCK = rand() % 6 * (rand() % 3 + 1);
	}
	else if (rand() % 100 >= 90 && rand() % 100 < 95)
	{
		strcpy(preItem.ITEM_NAME, "六道杖");
		preItem.ITEM_LIFE = rand() % 5 + (rand() % (pPlayer + *pExSel)->LEVEL);
		preItem.ITEM_ATK = rand() % 5 + (rand() % (pPlayer + *pExSel)->LEVEL);
		preItem.ITEM_DEF = rand() % 5 + (rand() % (pPlayer + *pExSel)->LEVEL);
		preItem.ITEM_MATK = rand() % 5 + (rand() % (pPlayer + *pExSel)->LEVEL) * (rand() % 3 + 1);
		preItem.ITEM_MDEF = rand() % 5 + (rand() % (pPlayer + *pExSel)->LEVEL) * (rand() % 3 + 1);
		preItem.ITEM_SPD = rand() % 5 + (rand() % (pPlayer + *pExSel)->LEVEL) * (rand() % 2 + 1);
		preItem.ITEM_LUCK = rand() % 6 * (rand() % 4 + 1);
	}
	else
	{
		strcpy(preItem.ITEM_NAME, "夜叉槍");
		preItem.ITEM_LIFE = rand() % 5 + (rand() % (pPlayer + *pExSel)->LEVEL);
		preItem.ITEM_ATK = rand() % 5 + (rand() % (pPlayer + *pExSel)->LEVEL) * (rand() % 4 + 1);
		preItem.ITEM_DEF = rand() % 5 + (rand() % (pPlayer + *pExSel)->LEVEL);
		preItem.ITEM_MATK = rand() % 5 + (rand() % (pPlayer + *pExSel)->LEVEL) * (rand() % 2 + 1);
		preItem.ITEM_MDEF = rand() % 5 + (rand() % (pPlayer + *pExSel)->LEVEL);
		preItem.ITEM_SPD = rand() % 5 + (rand() % (pPlayer + *pExSel)->LEVEL) * (rand() % 3 + 1);
		preItem.ITEM_LUCK = rand() % 6 * (rand() % 3 + 1);
	}
	gotoxy(*pX, *pY);
	printf("宝箱には%sが入っていた！ 【 体力+:%d 攻撃力+:%d 防御力+:%d 魔力+:%d 魔防+:%d 素早さ+:%d 運+:%d 】\n", preItem.ITEM_NAME, preItem.ITEM_LIFE, preItem.ITEM_ATK, preItem.ITEM_DEF, preItem.ITEM_MATK, preItem.ITEM_MDEF, preItem.ITEM_SPD, preItem.ITEM_LUCK);
	*pY = wherey();
	if (pItem->ITEM_NAME[0] != '\0')
	{
		gotoxy(*pX, *pY);
		printf("(現在装備中:%s 【 体力+:%d 攻撃力+:%d 防御力+:%d 魔力+:%d 魔防+:%d 素早さ+:%d 運+:%d 】)\n", pItem->ITEM_NAME, pItem->ITEM_LIFE, pItem->ITEM_ATK, pItem->ITEM_DEF, pItem->ITEM_MATK, pItem->ITEM_MDEF, pItem->ITEM_SPD, pItem->ITEM_LUCK);
		*pY = wherey();
	}
	gotoxy(*pX, *pY);
	printf("装備しますか？(はい:1/いいえ:2)＞");
	scanf("%d",&sel);
	*pY = *pY + 1;
	if (sel == 1)
	{
		*pItem = preItem;
		gotoxy(*pX, *pY);
		printf("%sを装備した！\n", pItem->ITEM_NAME);
		*pY = wherey();
	}
	else
	{
	}
}
//=============================
// 脱出
//=============================
void dungeonEscape(int* pEscape,int* pStair,int* pX,int* pY)
{
	gotoxy(*pX,*pY);
	printf("第%d階層\n", *pStair);
	*pY = wherey();
	gotoxy(*pX, *pY);
	printf("探索を続けますか？(はい:1/いいえ:2)＞");
	scanf("%d", &*pEscape);
}