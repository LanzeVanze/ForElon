#ifndef _CNOSPREAD_H_ 
#define _CNOSPREAD_H_

#include "sdk.h"

class cNoSpread
{
	public:
		cNoSpread();
		int m_iLastWeaponID;
		int GetWeaponID(const char *szWeaponName);
		void GetSpreadFix( UINT seed, float *fIn, float *fOut );
		float GetVecSpread( void );
		void GetGausSpread ( UINT seed, float *vec );
		void GetSpreadXY( UINT seed, float *vec );
		void VectorAngles( const float *forward, float *angles );
		void AngleVectors (const float *angles, float *forward, float *right, float *up);
};

class CShotManipulator
{
public:
	CShotManipulator( const Vector &vecForward )
	{
		SetShootDir( vecForward );
	};

	void SetShootDir( const Vector &vecForward )
	{
		m_vecShotDirection = vecForward;
		VectorVectors( m_vecShotDirection, m_vecRight, m_vecUp );
	}

	const Vector &ApplySpread( const Vector &vecSpread, float bias = 1.0 );

	const Vector &GetShotDirection()	{ return m_vecShotDirection; }
	const Vector &GetResult()			{ return m_vecResult; }
	const Vector &GetRightVector()		{ return m_vecRight; }
	const Vector &GetUpVector()			{ return m_vecUp;}

private:
	Vector m_vecShotDirection;
	Vector m_vecRight;
	Vector m_vecUp;
	Vector m_vecResult;
};


#endif
