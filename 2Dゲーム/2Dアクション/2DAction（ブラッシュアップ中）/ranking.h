//##################################################################################################################################################################//
//
// �����L���O�w�b�_�t�@�C�� [ranking.h]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//


#ifndef _RANKING_H_

#define _RANKING_H_

#include "main.h"


//�����L���O�̍\����
typedef struct
{
	int NewScore;
	int OldScore;
	int ChangScore;
}RANKING_SCORE;


//�v���g�^�C�v�錾
HRESULT InitRanking(void);
void UninitRanking(void);
void UpdateRanking(void);
void DrawRanking(void);
void OldRankingScore(void);
#endif