#include "Headers.h"

BuffBase::BuffBase()
{
    m_buffName = BuffName::Null;
    m_lifeTime = 0;
    m_currentLifeTime = m_lifeTime;
    m_alpha = 1.0f;
    m_aliveFlg = true;
}

bool BuffBase::Update()
{
    m_currentLifeTime--;
    if (m_currentLifeTime > 0)
    {
        m_aliveFlg = true;
        return true;
    }
    else
    {
        m_aliveFlg = false;
        return false;
    }

}
