/* Computer Graphics and Game Technology, Assignment Box2D game
 *
 * Student name ....
 * Student email ...
 * Collegekaart ....
 * Date ............
 * Comments ........
 *
 *
 * (always fill in these fields before submitting!!)
 */

#include <cstdio>

#include <GL/gl.h>
#include <GL/glut.h>
#include <Box2D/Box2D.h>

#include "levels.h"

unsigned int reso_x = 800, reso_y = 600; // Window size in pixels
const float world_x = 8.f, world_y = 6.f; // Level (world) size in meters

int last_time;
int frame_count;

// Information about the levels loaded from files will be available in these.
unsigned int num_levels;
level_t *levels;

b2Vec2 gravity(0.0f, -10.0f);
b2World world(gravity);


/*
 * Load a given world, i.e. read the world from the `levels' data structure and
 * convert it into a Box2D world.
 */
void load_world(unsigned int level)
{
    if (level >= num_levels)
    {
        // Note that level is unsigned but we still use %d so -1 is shown as
        // such.
        printf("Warning: level %d does not exist.\n", level);
        return;
    }
    // Create a Box2D world and populate it with all bodies for this level
    // (including the ball).
//  for (int i = 0; i < levels[level].num_polygons; i++)
//    levels[level].start



	b2BodyDef groundBodyDef;
	groundBodyDef.type = b2_staticBody;
	groundBodyDef.position.Set(4.0f,1.0f);
	b2Body *ground = world.CreateBody(&groundBodyDef);
	b2PolygonShape groundBox;
	groundBox.SetAsBox(3.0,1.0);
	b2FixtureDef fixtureGround;
	fixtureGround.shape = &groundBox;
	fixtureGround.density = 1.0f;
	fixtureGround.friction = 0.3f;
	ground->CreateFixture(&fixtureGround);

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(1.0f,4.0f);
	b2Body *body = world.CreateBody(&bodyDef);
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(1.0f,1.0f);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	body->CreateFixture(&fixtureDef);
	
	b2BodyDef bodyDef1;
	bodyDef1.type = b2_dynamicBody;
	bodyDef1.position.Set(3.0f,4.0f);
	b2Body *body1 = world.CreateBody(&bodyDef1);
	b2PolygonShape dynamicBox1;
	dynamicBox1.SetAsBox(1.0f,1.0f);
	b2FixtureDef fixtureDef1;
	fixtureDef1.shape = &dynamicBox1;
	fixtureDef1.density = 1.0f;
	fixtureDef1.friction = 0.3f;
	body1->CreateFixture(&fixtureDef1);
	
}


/*
 * Called when we should redraw the scene (i.e. every frame).
 * It will show the current framerate in the window title.
 */
void draw(void)
{
    int time = glutGet(GLUT_ELAPSED_TIME);
    int frametime = time - last_time;
    frame_count++;

    // Clear the buffer
    glColor3f(0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);


    //
    // Do any logic and drawing here.
    //
    world.Step((frametime / 1000.f) / frame_count, 6, 2);
	b2Body *objList = world.GetBodyList();

	printf("bodies: %d\n",world.GetBodyCount());
	for (int i=0; i<world.GetBodyCount(); i++) {
		b2Vec2 position = objList->GetPosition();
		float angle = objList->GetAngle();
		b2Fixture *fix = objList->GetFixtureList();
		b2Shape *shape = fix->GetShape();

		if (shape->GetType() == 2)  {
		
			b2PolygonShape *poly = (b2PolygonShape *) shape;
			int vertexCount = poly->GetVertexCount();
			printf("poly:%d\n",vertexCount);
			glBegin(GL_TRIANGLE_FAN);
			glColor3f(1,1,1);
			for (int v=0; v<vertexCount; v++) {
				b2Vec2 vex = objList->GetWorldPoint(poly->GetVertex(v));
				glVertex3f(vex.x, vex.y, 0.0f);
			}
			glEnd();
			glDrawArrays(GL_TRIANGLE_FAN,0,vertexCount);

		}
		objList = objList->GetNext();
	}
		

    // Show rendered frame
    glutSwapBuffers();

    // Display fps in window title.
    if (frametime >= 1000)
    {
        char window_title[128];
        snprintf(window_title, 128,
                "Box2D: %f fps, level %d/%d",
                frame_count / (frametime / 1000.f), -1, num_levels);
        glutSetWindowTitle(window_title);
        last_time = time;
        frame_count = 0;
    }
}

/*
 * Called when window is resized. We inform OpenGL about this, and save this
 * for future reference.
 */
void resize_window(int width, int height)
{
    glViewport(0, 0, width, height);
    reso_x = width;
    reso_y = height;
}

/*
 * Called when the user presses a key.
 */
void key_pressed(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27: // Esc
        case 'q':
            exit(0);
            break;
        // Add any keys you want to use, either for debugging or gameplay.
        default:
            break;
    }
}

/*
 * Called when the user clicked (or released) a mouse buttons inside the window.
 */
void mouse_clicked(int button, int state, int x, int y)
{

}

/*
 * Called when the mouse is moved to a certain given position.
 */
void mouse_moved(int x, int y)
{

}


int main(int argc, char **argv)
{
    // Create an OpenGL context and a GLUT window.
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(reso_x, reso_y);
    glutCreateWindow("Box2D");

    // Bind all GLUT events do callback function.
    glutDisplayFunc(&draw);
    glutIdleFunc(&draw);
    glutReshapeFunc(&resize_window);
    glutKeyboardFunc(&key_pressed);
    glutMouseFunc(&mouse_clicked);
    glutMotionFunc(&mouse_moved);
    glutPassiveMotionFunc(&mouse_moved);

    // Initialise the matrices so we have an orthogonal world with the same size
    // as the levels, and no other transformations.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, world_x, 0, world_y, 0, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Read the levels into a bunch of structs.
    num_levels = load_levels(&levels);
    printf("Loaded %d levels.\n", num_levels);

    // Load the first level (i.e. create all Box2D stuff).
    load_world(0);
    	
    last_time = glutGet(GLUT_ELAPSED_TIME);
    frame_count = 0;
    glutMainLoop();

    return 0;
}
