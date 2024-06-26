/*==============================================================================

  �Q�[���Ǘ�[game.h]
														Author :�ؓc �C���l
														Date   :2023/06/16
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once
#ifndef _GAME_H_
#define _GAME_H_

//*****************************************************************************
// �񋓑̐錾
//*****************************************************************************
enum GAME_DIFF { //�Q�[����Փx
    NORMAL = 0,
    HARD,
    FULL,
    OPTION,
    EXPLANATION
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);
void SetGameDiff(GAME_DIFF diff);
GAME_DIFF* GetGameDiff(void);
void SetPause(bool pause);

#endif // !_GAME_H_
