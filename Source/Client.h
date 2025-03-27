#ifndef __CLIENT__H
#define __CLIENT__H

#include <Windows.h>
#include "SDK.h"

struct CClient
{
	int	(__stdcall *Init)( CreateInterfaceFn appSystemFactory, CreateInterfaceFn physicsFactory, CGlobalVarsBase *pGlobals );
	void (__stdcall *Shutdown)( void );
	void (__stdcall *LevelInitPreEntity)( char const* pMapName );
	void (__stdcall *LevelInitPostEntity)( void );
	void (__stdcall *LevelShutdown)( void );
	ClientClass *(__stdcall *GetAllClasses)( void );
	int	 (__stdcall *HudVidInit)( void );
	void (__stdcall *HudProcessInput)( bool bActive );
	void (__stdcall *HudUpdate)( bool bActive );
	void (__stdcall *HudReset)( void );
	void (__stdcall *HudText)( const char * message );
	void (__stdcall *IN_ActivateMouse)( void );
	void (__stdcall *IN_DeactivateMouse)( void );
	void (__stdcall *IN_MouseEvent)(int mstate, bool down);
	void (__stdcall *IN_Accumulate)(void);
	void (__stdcall *IN_ClearStates)(void);
	bool (__stdcall *IN_IsKeyDown)( const char *name, bool& isdown );
	int	 (__stdcall *IN_KeyEvent)( int eventcode, int keynum, const char *pszCurrentBinding );
	void (__stdcall *CreateMove)( int sequence_number,	float input_sample_frametime,bool active );
	void (__stdcall *ExtraMouseSample)( float frametime, bool active );
	bool (__stdcall *WriteUsercmdDeltaToBuffer)( bf_write *buf, int from, int to, bool isnewcommand );
	void (__stdcall *EncodeUserCmdToBuffer)( bf_write& buf, int slot );
	void (__stdcall *DecodeUserCmdFromBuffer)( bf_read& buf, int slot );
	void (__stdcall *View_Render)( vrect_t *rect );
	void (__stdcall *RenderView)( const CViewSetup &view, bool drawViewmodel );
	void (__stdcall *View_Fade)( ScreenFade_t *pSF );
	void (__stdcall *SetCrosshairAngle)( const QAngle& angle );
	void (__stdcall *InitSprite)( CEngineSprite *pSprite, const char *loadname );
	void (__stdcall *ShutdownSprite)( CEngineSprite *pSprite );
	int	 (__stdcall *GetSpriteSize)( void );
	void (__stdcall *VoiceStatus)( int entindex, qboolean bTalking );
	void (__stdcall *InstallStringTableCallback)( char const *tableName );
	void (__stdcall *FrameStageNotify)( ClientFrameStage_t curStage );
	bool (__stdcall *DispatchUserMessage)( int msg_type, bf_read &msg_data );
	CSaveRestoreData *(__stdcall *SaveInit)( int size );
	void (__stdcall *SaveWriteFields)( CSaveRestoreData *, const char *, void *, datamap_t *, typedescription_t *, int );
	void (__stdcall *SaveReadFields)( CSaveRestoreData *, const char *, void *, datamap_t *, typedescription_t *, int );
	void (__stdcall *PreSave)( CSaveRestoreData * );
	void (__stdcall *Save)( CSaveRestoreData * );
	void (__stdcall *WriteSaveHeaders)( CSaveRestoreData * );
	void (__stdcall *ReadRestoreHeaders)( CSaveRestoreData * );
	void (__stdcall *Restore)( CSaveRestoreData *, bool );
	void (__stdcall *DispatchOnRestore)();
	CStandardRecvProxies* (__stdcall *GetStandardRecvProxies)();
	void (__stdcall *WriteSaveGameScreenshot)( const char *pFilename );
	void (__stdcall *EmitSentenceCloseCaption)( char const *tokenstream );
	void (__stdcall *EmitCloseCaption)( char const *captionname, float duration );
};

extern CClient gClient;
extern CClient* g_pHookedClient;

void __stdcall new_HudUpdate ( bool bActive );
void __stdcall new_CreateMove ( int sequence_number, float input_sample_frametime, bool active );

#endif