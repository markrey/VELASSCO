#pragma once



class EDM_interface
{
   Database                         *db;
protected:
   Model                            *m; // The opened EDM model
   SerializableModel                *sm;
   Repository                       *currentRepository;
   CMemoryAllocator                 model_ma;
   CMemoryAllocator                 extra_ma;
   dbSchema                         *currentSchema;
   char                             *currentSchemaName;
   char                             *serverName;
   int                              serverPort;
public:
   std::map<string, Model*>           models;
   EDM_interface()
   {
      currentRepository = NULL; model_ma.init(0x100000);
   }
   void                             setDatabase(Database *_db) { db = _db; }
   void                             setCurrentSession(const char *sessionID) { } 
   void                             setCurrentModel(const char *sessionID);
   void                             setCurrentRepository(Repository *r) { currentRepository = r; }
   void                             setCurrentSchemaName(const char *sn) { currentSchemaName = (char*)sn; }
   void                             setRemoteModel(char *modelName, char *serverName, int serverPort);
   void                             sendObjectsToServer();
};