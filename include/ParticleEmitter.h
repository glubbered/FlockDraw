#if !defined __PARTICLE_EMITTER_H__
#define __PARTICLE_EMITTER_H__

#include <list>
#include "cinder/Vector.h"
#include "cinder/Surface.h"
#include "cinder/gl/Texture.h"

#include "Particle.h"

//#define __USE_SPATIAL_GRID__

#if defined __USE_SPATIAL_GRID__
#include "Spatial2DGrid.h"
#endif

class b2World;

class ParticleEmitter
{
public:
  ParticleEmitter( void );
  virtual ~ParticleEmitter( void );

  void addParticles( int _aumont, int _group = -1 );

  virtual void draw( void );
  virtual void update( double _currentTime, double _delta );

  virtual void killAll( double _currentTime );

  std::list< Particle* >  m_particles;
  ci::Vec2f               m_position;
  double                  m_maxLifeTime;
  double                  m_minLifeTime;

  double                  m_fadeInTime;
  double                  m_fadeOutTime;

  float                   m_particlesPerSecond;

  // flocking vars
  float                   m_zoneRadiusSqrd;
  float                   m_repelStrength;
  float                   m_alignStrength;
  float                   m_attractStrength;
  float                   m_groupRepelStrength;
  float                   m_lowThresh;
  float                   m_highThresh;
  
  ci::Surface*            m_referenceSurface;
  ci::gl::Texture*        m_screenTexture;
  ci::Surface             m_screenSurface;

  // particle tweak
  float                   m_particleSizeRatio;
  float                   m_particleSpeedRatio;
  float                   m_dampness;
  float                   m_colorRedirection;



private:
  void updateParticlesQuadratic( double _currentTime, double _delta );

#if defined __USE_SPATIAL_GRID__
  void updateParticlesSpatial( double _currentTime, double _delta );

  typedef Spatial2DGrid< Particle, Particle::PointAccessFunctor > SpaceIndex;
  SpaceIndex             m_grid;
  
#endif
  float                  m_particlesPerSecondLeftOver;
};

#endif //__PARTICLE_EMITTER_H__
