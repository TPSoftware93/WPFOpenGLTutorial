// Il blocco ifdef seguente viene in genere usato per creare macro che semplificano
// l'esportazione da una DLL. Tutti i file all'interno della DLL sono compilati con il simbolo OPENGLLIB_EXPORTS
// definito nella riga di comando. Questo simbolo non deve essere definito in alcun progetto
// che usa questa DLL. In questo modo qualsiasi altro progetto i cui file di origine includono questo file vedranno le funzioni
// le funzioni di OPENGLLIB_API come se fossero importate da una DLL, mentre questa DLL considera i simboli
// definiti con questa macro come esportati.
#ifdef OPENGLLIB_EXPORTS
#define OPENGLLIB_API __declspec(dllexport)
#else
#define OPENGLLIB_API __declspec(dllimport)
#endif

extern "C" OPENGLLIB_API int* InitOpenglContext(int* windowHandle);
extern "C" OPENGLLIB_API void Clear();
extern "C" OPENGLLIB_API void ClearColor(float r, float g, float b);
extern "C" OPENGLLIB_API void ResizeViewport(int startX, int startY, int width, int height);
extern "C" OPENGLLIB_API void SwapWindowBuffers(int *windowHandler);

extern "C" OPENGLLIB_API void DrawTriangle(float r,float g, float b);

extern "C" OPENGLLIB_API void GetString(char* string,int length);
