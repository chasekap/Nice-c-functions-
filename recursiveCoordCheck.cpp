bool adjust(double& x, double& y,shared_ptr<Actor> const &hbx){
    if(dist(x,y,hbx->getX(),hbx->getY()) < SPRITE_RADIUS*2){
      do  //make sure in radius
      {
             x += randInt(-2, 2);
             y += randInt(-2, 2);
          
      }while(sqrt(pow((x-128),2) + pow((y-128),2)) > 120);
        
        adjust(x, y, hbx); //recursively randomly adjust until valid
    }
    return true;
    
};
