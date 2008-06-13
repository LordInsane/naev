/*
 * See Licensing and Copyright notice in naev.h
 */



#ifndef ECONOMY_H
#  define ECONOMY_H


typedef struct Commodity_ {
   char* name;
   char* description;
   int low, medium, high; /* prices */
} Commodity;

/* commodity stuff */
Commodity* commodity_get( const char* name );
int commodity_load (void);
void commodity_free (void);

/* misc stuff */
void credits2str( char *str, unsigned int credits, int decimals );
void commodity_Jettison( int pilot, Commodity* com, int quantity );


#endif /* ECONOMY_H */
