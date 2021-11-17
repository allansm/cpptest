#include <allansm/simple/glut/init.hpp>
#include <files.cpp>
#include <util.cpp>
#include <allansm/parser.hpp>

void test(int n){
	glutPostRedisplay();
	glutTimerFunc(1,test,0);
}

void test2(unsigned char c,int a,int b){
	glutPostRedisplay();
	if(c == 'd'){
		glRotatef(10,0,1,0);
	}

	if(c == 'a'){
		glRotatef(-10,0,1,0);
	}
	if(c == 'w'){
		glRotatef(10,1,0,0);
	}

	if(c == 's'){
		glRotatef(-10,1,0,0);
	}

}

main(int argc, char ** argv){
	auto t = glut(argc,argv);
		
	t.callback = [](){
		glClear(GL_COLOR_BUFFER_BIT);
		glBegin(GL_POLYGON);
		for(auto n : Files().getLines("test.txt")){
			if(n != "" & n != "\n"){
				auto tmp = Util().explode(n," ");
				float x = unknown(tmp[0]);
				float y = unknown(tmp[1]);
				float z = unknown(tmp[2]);

				glVertex3f(x,y,z);
			}
		}
		glEnd();
		glFlush();
	};

	t.after = [](){
		glutTimerFunc(1, test, 0);
		glutKeyboardFunc(test2);
	
	};

	t.start();
}
