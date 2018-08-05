
AppKernel_t* AppKernel_new();


void AppKernel_registerRoutes(AppKernel_t* this,Route_t* root);


void AppKernel_free(AppKernel_t* this);
