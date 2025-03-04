/*
 * See Licensing and Copyright notice in naev.h
 */
/**
 * @file pilot_ship.c
 *
 * @brief Handles pilot ship Lua stuff.
 */
/** @cond */
#include "naev.h"
/** @endcond */

#include "nlua_pilot.h"
#include "nlua_ship.h"

static void pilot_shipLmem( Pilot *p )
{
   /* Set the memory. */
   lua_rawgeti( naevL, LUA_REGISTRYINDEX, p->lua_ship_mem ); /* mem */
   nlua_setenv( naevL, p->ship->lua_env, "mem" );
}
static void shipLRunWarning( const Pilot *p, const Ship *s, const char *name, const char *error )
{
   WARN( _("Pilot '%s''s ship '%s' -> '%s':\n%s"), p->name, s->name, name, error );
}

/**
 * @brief Initializes the pilot ship Lua.
 *
 *    @param p Pilot to set up memory for.
 *    @return 0 on success.
 */
int pilot_shipLInit( Pilot *p )
{
   if (p->lua_ship_mem == LUA_NOREF) {
      lua_newtable( naevL ); /* mem */
      p->lua_ship_mem = luaL_ref( naevL, LUA_REGISTRYINDEX ); /* */
   }

   if (p->ship->lua_init == LUA_NOREF)
      return 0;

   pilot_shipLmem( p );

   /* Set up the function: init( p ) */
   lua_rawgeti( naevL, LUA_REGISTRYINDEX, p->ship->lua_init ); /* f */
   lua_pushpilot( naevL, p->id ); /* f, p */
   if (nlua_pcall( p->ship->lua_env, 1, 0 )) { /* */
      shipLRunWarning( p, p->ship, "init", lua_tostring(naevL,-1) );
      lua_pop(naevL, 1);
      return -1;
   }
   return 1;
}

/**
 * @brief Cleans up the pilot ship Lua.
 *
 *    @param p Pilot to set up memory for.
 *    @return 0 on success.
 */
int pilot_shipLCleanup( Pilot *p )
{
   if (p->ship->lua_cleanup != LUA_NOREF) {
      pilot_shipLmem( p );

      /* Set up the function: cleanup( p ) */
      lua_rawgeti( naevL, LUA_REGISTRYINDEX, p->ship->lua_cleanup ); /* f */
      lua_pushpilot( naevL, p->id ); /* f, p */
      if (nlua_pcall( p->ship->lua_env, 1, 0 )) { /* */
         shipLRunWarning( p, p->ship, "cleanup", lua_tostring(naevL,-1) );
         lua_pop(naevL, 1);
         return -1;
      }
   }

   /* Clear Lua if necessary. */
   if (p->lua_ship_mem != LUA_NOREF) {
      luaL_unref( naevL, LUA_REGISTRYINDEX, p->lua_ship_mem );
      p->lua_ship_mem = LUA_NOREF;
   }
   return 0;
}

/**
 * @brief Updates the pilot Lua stuff.
 *
 *    @param p Pilot to set up memory for.
 *    @param dt Time delta-tick.
 *    @return 0 on success.
 */
int pilot_shipLUpdate( Pilot *p, double dt )
{
   if (p->ship->lua_update == LUA_NOREF)
      return 0;

   /* Set up the function: update( p ) */
   lua_rawgeti( naevL, LUA_REGISTRYINDEX, p->ship->lua_update ); /* f */
   lua_pushpilot( naevL, p->id ); /* f, p */
   lua_pushnumber( naevL, dt ); /* f, p, dt */
   if (nlua_pcall( p->ship->lua_env, 2, 0 )) { /* */
      shipLRunWarning( p, p->ship, "update", lua_tostring(naevL,-1) );
      lua_pop(naevL, 1);
      return -1;
   }
   return 0;
}

/**
 * @brief Initializes the pilot explosion stuff.
 *
 *    @param p Pilot to set up memory for.
 *    @return 0 on success.
 */
int pilot_shipLExplodeInit( Pilot *p )
{
   if (p->ship->lua_explode_init == LUA_NOREF)
      return 0;
   pilot_shipLmem( p );

   /* Set up the function: explode_init( p ) */
   lua_rawgeti( naevL, LUA_REGISTRYINDEX, p->ship->lua_explode_init ); /* f */
   lua_pushpilot( naevL, p->id ); /* f, p */
   if (nlua_pcall( p->ship->lua_env, 1, 0 )) { /* */
      shipLRunWarning( p, p->ship, "explode_init", lua_tostring(naevL,-1) );
      lua_pop(naevL, 1);
      return -1;
   }
   return 0;
}

/**
 * @brief Updates the pilot explosion Lua stuff.
 *
 *    @param p Pilot to set up memory for.
 *    @param dt Time delta-tick.
 *    @return 0 on success.
 */
int pilot_shipLExplodeUpdate( Pilot *p, double dt )
{
   if (p->ship->lua_explode_update == LUA_NOREF)
      return 0;
   pilot_shipLmem( p );

   /* Set up the function: explode_update( p ) */
   lua_rawgeti( naevL, LUA_REGISTRYINDEX, p->ship->lua_explode_update ); /* f */
   lua_pushpilot( naevL, p->id ); /* f, p */
   lua_pushnumber( naevL, dt ); /* f, p, dt */
   if (nlua_pcall( p->ship->lua_env, 2, 0 )) { /* */
      shipLRunWarning( p, p->ship, "explode_update", lua_tostring(naevL,-1) );
      lua_pop(naevL, 1);
      return -1;
   }
   return 0;
}
