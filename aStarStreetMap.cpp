//Uses unordered maps and a priority queue to implement A* to enable point to point navigation optimally 
//Implements a stack to return the route in correct order

DeliveryResult PointToPointRouterImpl::generatePointToPointRoute(
        const GeoCoord& start,
        const GeoCoord& end,
        list<StreetSegment>& route,
        double& totalDistanceTravelled) const
{

  if(start == end) {//trivial solution
    totalDistanceTravelled = 0;
    return DELIVERY_SUCCESS;
  }



  priority_queue<pair<double,GeoCoord>,std::vector<pair<double,GeoCoord>> , greater<pair<double,GeoCoord>>> nextUp; //Minheap
  vector<StreetSegment> segsS;
  vector<StreetSegment> segsF;

  if(!msm->getSegmentsThatStartWith(start,segsS) || !msm->getSegmentsThatStartWith(end,segsF)){
    return BAD_COORD;}
  ExpandableHashMap<GeoCoord,pair<GeoCoord,string>> pathTo;
  ExpandableHashMap<GeoCoord,double> costTo;
  nextUp.push(make_pair(0,start));
  pathTo.associate(start,make_pair(start,"here"));
  costTo.associate(start,0);
while(!nextUp.empty()){ //O(N) + O(N) + O(N) + O(4) -> O(N)
  auto current = nextUp.top().second;
  nextUp.pop();
  if(current == end){
    totalDistanceTravelled = *costTo.find(current);
    stack<StreetSegment> stx; // use a stack to return directions in right order
    while(current != start){ //Worst case O(N), but will only ever run once
      auto s = *pathTo.find(current); 
      StreetSegment seggy(s.first,current,s.second);
      stx.push(seggy);
      current = s.first;
    }
    while(!stx.empty()){
      route.push_back(stx.top());
      stx.pop();
    }
    return DELIVERY_SUCCESS;;
  }
  msm->getSegmentsThatStartWith(current,segsS);
  //std::cerr.precision(10);
  for(auto x : segsS){ // up to O(4)
      auto next = x.end;
      string name = x.name;
      double dx = *costTo.find(current) + distanceEarthMiles(current,next); //distance between nodes
      double dg = distanceEarthMiles(x.end, end) * .3;  //heuristic cost must not overestimate distance

      double cost = dx + dg;
      if(costTo.find(next) == nullptr || dx < *costTo(next)){ 
      pathTo.associate(next,make_pair(current,name)); //so we can save the name of the street
      costTo.associate(next,dx);
      nextUp.push(make_pair(cost,next));
    }

  }

}

  return NO_ROUTE; // Delete this line and implement this function correctly
}
