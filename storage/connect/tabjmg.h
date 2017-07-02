/**************** tabjmg H Declares Source Code File (.H) **************/
/*  Name: tabjmg.h   Version 1.0                                       */
/*                                                                     */
/*  (C) Copyright to the author Olivier BERTRAND          2017         */
/*                                                                     */
/*  This file contains the MongoDB classes using the Java Driver.      */
/***********************************************************************/
#include "mongo.h"
#include "jmgoconn.h"
#include "jdbccat.h"

/* -------------------------- TDBJMG class --------------------------- */

/***********************************************************************/
/*  This is the MongoDB Table Type using the Java Driver.              */
/*  The table is a collection, each record being a document.           */
/***********************************************************************/
class DllExport TDBJMG : public TDBEXT {
	friend class JMGCOL;
	friend class MGODEF;
	friend class MGODISC;
	friend class JAVAConn;
	friend PQRYRES MGOColumns(PGLOBAL, PCSZ, PCSZ, PTOS, bool);
public:
	// Constructor
	TDBJMG(PMGODEF tdp);
	TDBJMG(TDBJMG *tdbp);

	// Implementation
	virtual AMT  GetAmType(void) { return TYPE_AM_MGO; }
	virtual PTDB Duplicate(PGLOBAL g) { return (PTDB)new(g) TDBJMG(this); }

	// Methods
	virtual PTDB Clone(PTABS t);
	virtual PCOL MakeCol(PGLOBAL g, PCOLDEF cdp, PCOL cprec, int n);
	virtual PCOL InsertSpecialColumn(PCOL colp);
//virtual void SetFilter(PFIL fp);
	virtual int  RowNumber(PGLOBAL g, bool b = FALSE) { return N; }

	// Database routines
	virtual int  Cardinality(PGLOBAL g);
	virtual int  GetMaxSize(PGLOBAL g);
	virtual bool OpenDB(PGLOBAL g);
	virtual int  ReadDB(PGLOBAL g);
	virtual int  WriteDB(PGLOBAL g);
	virtual int  DeleteDB(PGLOBAL g, int irc);
	virtual void CloseDB(PGLOBAL g);
	virtual bool ReadKey(PGLOBAL g, OPVAL op, const key_range *kr);

protected:
	bool Init(PGLOBAL g);

	// Members
	JMgoConn  *Jcp;                // Points to a Mongo connection class
//JMGCOL    *Cnp;                // Points to count(*) column
	JDBCPARM   Ops;                // Additional parameters
	PCSZ       Uri;
	PCSZ       Db_name;
	PCSZ       Coll_name;
	PCSZ       Options;		         // The MongoDB options
	PCSZ       Filter;			       // The filtering query
	PSZ        Wrapname;           // Java wrapper name
	int        Fpos;               // The current row index
	int        N;                  // The current Rownum
	int        B;                  // Array index base
	bool       Done;			         // Init done
	bool       Pipe;			         // True for pipeline
}; // end of class TDBJMG

/* --------------------------- JMGCOL class -------------------------- */

/***********************************************************************/
/*  Class JMGCOL: MongoDB access method column descriptor.             */
/***********************************************************************/
class DllExport JMGCOL : public EXTCOL {
	friend class TDBJMG;
	friend class FILTER;
public:
	// Constructors
	JMGCOL(PGLOBAL g, PCOLDEF cdp, PTDB tdbp, PCOL cprec, int i);
	JMGCOL(JMGCOL *colp, PTDB tdbp); // Constructor used in copy process

	// Implementation
	virtual int   GetAmType(void) {return Tmgp->GetAmType();}

	// Methods
	//virtual bool SetBuffer(PGLOBAL g, PVAL value, bool ok, bool check);
	virtual PSZ   GetJpath(PGLOBAL g, bool proj);
	virtual void  ReadColumn(PGLOBAL g);
	virtual void  WriteColumn(PGLOBAL g);
//bool AddValue(PGLOBAL g, bson_t *doc, char *key, bool upd);

protected:
	// Default constructor not to be used
	JMGCOL(void) {}
//char *GetProjPath(PGLOBAL g);
//char *Mini(PGLOBAL g, const bson_t *bson, bool b);

	// Members
	TDBJMG *Tmgp;                 // To the MGO table block
	char   *Jpath;                // The json path
//char   *Mbuf;									// The Mini buffer
}; // end of class JMGCOL

#if 0
/***********************************************************************/
/*  This is the class declaration for the MONGO catalog table.         */
/***********************************************************************/
class DllExport TDBGOL : public TDBCAT {
public:
	// Constructor
	TDBGOL(PMGODEF tdp);

protected:
	// Specific routines
	virtual PQRYRES GetResult(PGLOBAL g);

	// Members
	PTOS  Topt;
	char *Db;
}; // end of class TDBGOL
#endif 0
