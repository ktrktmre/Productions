#pragma once
class Helth
{
private:
	float m_nowhp;
	float m_maxhelth;
public:
	Helth() { m_maxhelth = 0; m_nowhp = 0; };
	~Helth() {};
	void SetmaxHelth(float hp) { m_maxhelth = hp;};
	void SetNowHelth(float hp) { m_nowhp = hp; };
	float GetHelthGap() { return m_nowhp / m_maxhelth; };
	float GetMaxHelth() { return m_maxhelth; };
	float GetNowHelth() { return m_nowhp; };
	void AddDamage(float damage) { m_nowhp - damage > 0 ? m_nowhp -= damage : m_nowhp = 0; };
	void Addheal(float heal) { m_nowhp + heal > m_maxhelth ? m_nowhp = m_maxhelth : m_nowhp += heal; };

};

