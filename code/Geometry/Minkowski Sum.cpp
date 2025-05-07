void reorder_polygon(vector<PT>& P){
  size_t pos = 0;
  for(size_t i = 1; i < P.size(); i++){
    if(pii(P[i].y, P[i].x) < pii(P[pos].y, P[pos].x)) pos = i;
  }
  rotate(P.begin(), P.begin() + pos, P.end());
}

vector<PT> minkowski(vector<PT> &P, vector<PT> &Q){
  reorder_polygon(P); reorder_polygon(Q);
  P.push_back(P[0]); P.push_back(P[1]);
  Q.push_back(Q[0]); Q.push_back(Q[1]);
  vector<PT> result;
  size_t i = 0, j = 0;
  while(i < P.size() - 2 or j < Q.size() - 2){
    result.push_back(P[i] + Q[j]);
    auto vprod = cross((P[i + 1] - P[i]), (Q[j + 1] - Q[j]));
    if(vprod >= 0 && i < P.size() - 2) ++i;
    if(vprod <= 0 && j < Q.size() - 2) ++j;
  } return result;
}