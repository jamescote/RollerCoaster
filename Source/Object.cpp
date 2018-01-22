#include "Object.h"
#include "TextureManager.h"

// Default Construtor to initialize position and ID
Object::Object( const vec3* pPos, long lID, const string* sTexName, const Anim_Track* pAnimTrack )
{
	m_pPosition = *pPos;
	m_lID = lID;

	if( !sTexName->empty() )
		m_pTexture = TextureManager::getInstance()->loadTexture( *sTexName, lID );
	else m_pTexture = NULL;

	if ( NULL != pAnimTrack )
		m_pAnimTrack = new Anim_Track( *pAnimTrack );
	else m_pAnimTrack = NULL;
}

// Copy Constructor
Object::Object( const Object* pCopy )
{
	m_pPosition = pCopy->m_pPosition;
	m_lID = pCopy->m_lID;

	if ( NULL != m_pTexture )
		TextureManager::getInstance()->unloadTexture( m_pTexture->getFileName(), m_lID );
	else m_pTexture = NULL;

	m_pAnimTrack = pCopy->m_pAnimTrack;
}

// Destructor: unload Texture.
Object::~Object()
{
	if( NULL != m_pTexture )
		TextureManager::getInstance()->unloadTexture( m_pTexture->getFileName(), m_lID );

	if ( NULL != m_pAnimTrack )
		delete m_pAnimTrack;
}

// Changes the Texture of the Object.  Given a Texture Location, it will attempt to
// Load the new texture first to see if it can be loaded.  If it can, it will unload its
// current texture and store the new texture.
void Object::switchTexture( const string* sTexLoc )
{
	TextureManager* pTxMngr = TextureManager::getInstance();
	Texture* pNewTexture = pTxMngr->loadTexture( *sTexLoc, m_lID );

	if ( NULL != pNewTexture )
	{
		pTxMngr->unloadTexture( m_pTexture->getFileName(), m_lID );
		m_pTexture = pNewTexture;
	}
}
