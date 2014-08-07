
//modelTest::modelTest(string type) {
//	name = type;
//
//}
//
//void modelTest::build(float lookupdown, float sceneroty,float xtrans,float ytrans,float ztrans) {
//
//	if(displayType != true) {
//		buildModel(lookupdown,sceneroty,xtrans, ytrans, ztrans);
//	}
//	else {
//		buildList(lookupdown,sceneroty,xtrans, ytrans, ztrans);
//	}
//}
//
//void modelTest::moveModel(float lookupdown, float sceneroty,float xtrans,float ytrans,float ztrans,int a) {
//
//}
//
//void modelTest::updateModel() {
//
//}
//
//void modelTest::updateState() {
//
//}
//
//int modelTest::getOverallState() {
//	return 0;
//}
//
//void modelTest::buildModel(float lookupdown, float sceneroty,float xtrans,float ytrans,float ztrans) {
//	GLfloat x_m, y_m, z_m, u_m, v_m;
//
//	for(int a = 0; a<display.getPolys().size() - 1;a++) {
//		moveModel(lookupdown,sceneroty,xtrans, ytrans, ztrans,a);
//		if(display.getPolys()[a]->getTotalVert() == 3) {
//			
//			glBegin(GL_TRIANGLES);
//
//		}
//		else if(display.getPolys()[a]->getTotalVert() == 4) {
//			glBegin(GL_QUADS);
//		}
//		glNormal3f( 0.0f, 0.0f, 1.0f);
//		for(int b = 0; b<display.getPolys()[a]->getTotalVert();b++) {
//			
//			x_m = display.getPolys()[a]->getVertex(b).getX();
//			y_m = display.getPolys()[a]->getVertex(b).getY();
//			z_m = display.getPolys()[a]->getVertex(b).getZ();
//			u_m = display.getPolys()[a]->getVertex(b).getU();
//			v_m = display.getPolys()[a]->getVertex(b).getV();
//			glTexCoord2f(u_m,v_m); glVertex3f(x_m,y_m,z_m);
//		
//		}
//		glEnd();
//	}
//	updateModel();
//}
//
//void modelTest::buildList(float lookupdown, float sceneroty,float xtrans,float ytrans,float ztrans) {
//	moveModel(lookupdown,sceneroty,xtrans,ytrans,ztrans,0);
//	//glCallList(displayList);
//}
////shape modelTest::getShape() {
////	return display;
////}