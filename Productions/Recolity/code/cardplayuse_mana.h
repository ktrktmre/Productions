#pragma once
#define CARD_MANA_MAX (6.0f)//max値
#define CARD_MANA_REGEN (1.0f / 60.0f)//(f)
class CardPlay_Use_Mana
{
private:
	float m_CardMana = 0;//マナ
public:
	CardPlay_Use_Mana() { m_CardMana = 0; };
	~CardPlay_Use_Mana() {};
	//更新処理
	void Update() {
		//マナの自動回復
		m_CardMana < CARD_MANA_MAX ? m_CardMana+= CARD_MANA_REGEN : m_CardMana = CARD_MANA_MAX;
	}
	//現在のマナの量を取得する
	float GetMana() { return m_CardMana; };
	//マナを減少させる
	void ReduceMana(float nu) { m_CardMana - nu < 0 ? m_CardMana = 0 : m_CardMana -= nu; };
	//マナを増加させる
	void IncreaseMana(float nu) { m_CardMana + nu > CARD_MANA_MAX ? m_CardMana = CARD_MANA_MAX : m_CardMana += nu; };
};
