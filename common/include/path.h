struct path { int x; int y; };
struct coords { int x; int y; int w; int h; };

int calcMaxPathLength(int w, int h);
int pathPos(struct coords path, int dist, int xy);
int multiplyPath(struct container *screen, struct coords *area);
