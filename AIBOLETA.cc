#include "Player.hh"

/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME BOLETA

struct PLAYER_NAME : public Player {
  /**
   * Factory: returns a new instance of this class.
   * Do not modify this function.
   */
  static Player* factory() { return new PLAYER_NAME; }

  /**
   * Types and attributes for your player can be defined here.
   */
  ////// DECLARACIONS ////
  const vector<Dir> dirs = {Down, Right, Up, Left};
  typedef vector<bool> vb;
  typedef vector<vb> mb;
  typedef vector<int> vi;
  typedef vector<vi> mi;

  ///////////////////// FUNCIONS BFS///////////////////////

  Pos bfs_money(int id) {
    mb visited(board_rows(), vb(board_cols(), false));
    queue<Pos> q;
    Pos p = citizen(id).pos;

    visited[p.i][p.j] = true;
    q.push(p);

    while (not q.empty()) {
      Pos act = q.front();
      q.pop();

      for (int k = 0; k < 4; ++k) {
        Pos seg = act + dirs[k];

        if (pos_ok(seg) and cell(seg).type != Building and
            not visited[seg.i][seg.j] and cell(seg).id == -1) {
          visited[seg.i][seg.j] = true;

          if (cell(seg).bonus == Money) {
            // cerr << "SOY :" << p << " HE ENCONTRADO DINERO EN " << seg
            //<< endl;
            return seg;
          }

          q.push(seg);
        }
      }
    }
    return Pos(-1, -1);
  }

  Pos bfs_food(int id) {
    mb visited(board_rows(), vb(board_cols(), false));
    queue<Pos> q;
    Pos p = citizen(id).pos;

    visited[p.i][p.j] = true;
    q.push(p);

    while (not q.empty()) {
      Pos act = q.front();
      q.pop();

      for (int k = 0; k < 4; ++k) {
        Pos seg = act + dirs[k];

        if (pos_ok(seg) and cell(seg).type != Building and
            not visited[seg.i][seg.j] and cell(seg).id == -1) {
          visited[seg.i][seg.j] = true;

          if (cell(seg).bonus == Food) {
            // cerr << "SOY :" << p << " HE ENCONTRADO DINERO EN " << seg
            //<< endl;
            return seg;
          }

          q.push(seg);
        }
      }
    }
    return Pos(-1, -1);
  }

  Pos bfs_weapon(int id) {
    mb visited(board_rows(), vb(board_cols(), false));
    queue<Pos> q;
    Pos p = citizen(id).pos;

    visited[p.i][p.j] = true;
    q.push(p);

    while (not q.empty()) {
      Pos act = q.front();
      q.pop();

      for (int k = 0; k < 4; ++k) {
        Pos seg = act + dirs[k];

        if (pos_ok(seg) and cell(seg).type != Building) {
          if (not visited[seg.i][seg.j] and cell(seg).id == -1) {
            visited[seg.i][seg.j] = true;

            if (cell(seg).weapon == Bazooka) return seg;
            q.push(seg);
          }
        }
      }
    }
    return Pos(-1, -1);
  }

  Pos bfs_attack_hammer(int id) {
    mb visited(board_rows(), vb(board_cols(), false));
    queue<Pos> q;
    Pos p = citizen(id).pos;

    visited[p.i][p.j] = true;
    q.push(p);

    while (not q.empty()) {
      Pos act = q.front();
      q.pop();

      for (int k = 0; k < 4; ++k) {
        Pos seg = act + dirs[k];

        if (pos_ok(seg) and cell(seg).type != Building and
            not visited[seg.i][seg.j] and
            (cell(seg).id == -1 or citizen(cell(seg).id).weapon == Hammer) and
            citizen(cell(seg).id).player != me() and
            cell(seg).resistance == -1) {
          visited[seg.i][seg.j] = true;
          if (citizen(cell(seg).id).weapon == Hammer) return seg;

          q.push(seg);
        }
      }
    }
    return Pos(-1, -1);
  }

  Pos bfs_attack_gun(int id) {
    mb visited(board_rows(), vb(board_cols(), false));
    queue<Pos> q;
    Pos p = citizen(id).pos;

    visited[p.i][p.j] = true;
    q.push(p);

    while (not q.empty()) {
      Pos act = q.front();
      q.pop();

      for (int k = 0; k < 4; ++k) {
        Pos seg = act + dirs[k];

        if (pos_ok(seg) and cell(seg).type != Building and
            not visited[seg.i][seg.j] and
            (cell(seg).id == -1 or citizen(cell(seg).id).weapon == Gun) and
            citizen(cell(seg).id).player != me() and
            cell(seg).resistance == -1) {
          visited[seg.i][seg.j] = true;
          if (citizen(cell(seg).id).weapon == Gun) return seg;

          q.push(seg);
        }
      }
    }
    return Pos(-1, -1);
  }

  Pos bfs_attack_bazooka(int id) {
    mb visited(board_rows(), vb(board_cols(), false));
    queue<Pos> q;
    Pos p = citizen(id).pos;

    visited[p.i][p.j] = true;
    q.push(p);

    while (not q.empty()) {
      Pos act = q.front();
      q.pop();

      for (int k = 0; k < 4; ++k) {
        Pos seg = act + dirs[k];

        if (pos_ok(seg) and cell(seg).type != Building and
            not visited[seg.i][seg.j] and
            (cell(seg).id == -1 or citizen(cell(seg).id).weapon == Bazooka) and
            citizen(cell(seg).id).player != me() and
            cell(seg).resistance == -1) {
          visited[seg.i][seg.j] = true;
          if (citizen(cell(seg).id).weapon == Bazooka and
              citizen(cell(seg).id).life < citizen(id).life)
            return seg;

          q.push(seg);
        }
      }
    }
    return Pos(-1, -1);
  }

  Pos bfs_attack_builders(int id) {
    mb visited(board_rows(), vb(board_cols(), false));
    queue<Pos> q;
    Pos p = citizen(id).pos;

    visited[p.i][p.j] = true;
    q.push(p);

    while (not q.empty()) {
      Pos act = q.front();
      q.pop();

      for (int k = 0; k < 4; ++k) {
        Pos seg = act + dirs[k];

        if (pos_ok(seg) and cell(seg).type != Building and
            not visited[seg.i][seg.j] and
            (cell(seg).id == -1 or citizen(cell(seg).id).type == Builder) and
            citizen(cell(seg).id).player != me() and
            cell(seg).resistance == -1) {
          visited[seg.i][seg.j] = true;
          if (citizen(cell(seg).id).type == Builder) return seg;

          q.push(seg);
        }
      }
    }
    return Pos(-1, -1);
  }

  ////////////////////// FUNCIONS "DIJKSTRA"///////////////

  Dir Calculate_path(int id, Pos p) {
    mi dist(board_rows(), vi(board_cols(), -1));
    queue<Pos> q;

    dist[p.i][p.j] = 0;
    q.push(p);

    bool found = false;

    while (not q.empty() and not found) {
      Pos act = q.front();
      q.pop();

      for (int k = 0; k < 4; ++k) {  // miro les quatre direccions possibles
        Pos seg = act + dirs[k];

        if (pos_ok(seg) and cell(seg).type != Building and
            dist[seg.i][seg.j] == -1 and
            citizen(cell(seg).id).player != me() and
            cell(seg).resistance == -1 and cell(seg).id == -1) {
          dist[seg.i][seg.j] = dist[act.i][act.j] + 1;

          if (seg == citizen(id).pos) found = true;
          q.push(seg);
        }
      }
    }

    int min = 34;
    Dir ret = dirs[random(0, 3)];
    for (int i = 0; i < 4; ++i) {
      Pos nou = (citizen(id).pos + dirs[i]);
      if (pos_ok(nou)) {
        if (dist[nou.i][nou.j] < min and dist[nou.i][nou.j] != -1) {
          min = dist[nou.i][nou.j];
          ret = dirs[i];
        }
      }
    }
    return ret;
  }

  Dir Path_for_hammer(int id, Pos p) {
    mi dist(board_rows(), vi(board_cols(), -1));
    queue<Pos> q;

    dist[p.i][p.j] = 0;
    q.push(p);

    bool found = false;

    while (not q.empty() and not found) {
      Pos act = q.front();
      q.pop();

      for (int k = 0; k < 4; ++k) {  // miro les quatre direccions possibles
        Pos seg = act + dirs[k];

        if (pos_ok(seg) and cell(seg).type != Building and
            dist[seg.i][seg.j] == -1 and
            (cell(seg).id == -1 or citizen(cell(seg).id).weapon == Hammer) and
            citizen(cell(seg).id).player != me() and
            cell(seg).resistance == -1) {
          dist[seg.i][seg.j] = dist[act.i][act.j] + 1;

          if (seg == citizen(id).pos) found = true;
          q.push(seg);
        }
      }
    }

    int min = 34;
    Dir ret = dirs[random(0, 3)];
    for (int i = 0; i < 4; ++i) {
      Pos nou = (citizen(id).pos + dirs[i]);
      if (pos_ok(nou)) {
        if (dist[nou.i][nou.j] < min and dist[nou.i][nou.j] != -1) {
          min = dist[nou.i][nou.j];
          ret = dirs[i];
        }
      }
    }
    return ret;
  }

  Dir Path_for_gun(int id, Pos p) {
    mi dist(board_rows(), vi(board_cols(), -1));
    queue<Pos> q;

    dist[p.i][p.j] = 0;
    q.push(p);

    bool found = false;

    while (not q.empty() and not found) {
      Pos act = q.front();
      q.pop();

      for (int k = 0; k < 4; ++k) {  // miro les quatre direccions possibles
        Pos seg = act + dirs[k];

        if (pos_ok(seg) and cell(seg).type != Building and
            dist[seg.i][seg.j] == -1 and
            (cell(seg).id == -1 or citizen(cell(seg).id).weapon == Gun) and
            citizen(cell(seg).id).player != me() and
            cell(seg).resistance == -1) {
          dist[seg.i][seg.j] = dist[act.i][act.j] + 1;

          if (seg == citizen(id).pos) found = true;
          q.push(seg);
        }
      }
    }

    int min = 34;
    Dir ret = dirs[random(0, 3)];
    for (int i = 0; i < 4; ++i) {
      Pos nou = (citizen(id).pos + dirs[i]);
      if (pos_ok(nou)) {
        if (dist[nou.i][nou.j] < min and dist[nou.i][nou.j] != -1) {
          min = dist[nou.i][nou.j];
          ret = dirs[i];
        }
      }
    }
    return ret;
  }

  Dir Path_for_bazooka(int id, Pos p) {
    mi dist(board_rows(), vi(board_cols(), -1));
    queue<Pos> q;

    dist[p.i][p.j] = 0;
    q.push(p);

    bool found = false;

    while (not q.empty() and not found) {
      Pos act = q.front();
      q.pop();

      for (int k = 0; k < 4; ++k) {  // miro les quatre direccions possibles
        Pos seg = act + dirs[k];

        if (pos_ok(seg) and cell(seg).type != Building and
            dist[seg.i][seg.j] == -1 and
            (cell(seg).id == -1 or citizen(cell(seg).id).weapon == Bazooka) and
            citizen(cell(seg).id).player != me() and
            cell(seg).resistance == -1) {
          dist[seg.i][seg.j] = dist[act.i][act.j] + 1;

          if (seg == citizen(id).pos) found = true;
          q.push(seg);
        }
      }
    }

    int min = 34;
    Dir ret = dirs[random(0, 3)];
    for (int i = 0; i < 4; ++i) {
      Pos nou = (citizen(id).pos + dirs[i]);
      if (pos_ok(nou)) {
        if (dist[nou.i][nou.j] < min and dist[nou.i][nou.j] != -1) {
          min = dist[nou.i][nou.j];
          ret = dirs[i];
        }
      }
    }
    return ret;
  }

  Dir Path_for_builder(int id, Pos p) {
    mi dist(board_rows(), vi(board_cols(), -1));
    queue<Pos> q;

    dist[p.i][p.j] = 0;
    q.push(p);

    bool found = false;

    while (not q.empty() and not found) {
      Pos act = q.front();
      q.pop();

      for (int k = 0; k < 4; ++k) {  // miro les quatre direccions possibles
        Pos seg = act + dirs[k];

        if (pos_ok(seg) and cell(seg).type != Building and
            dist[seg.i][seg.j] == -1 and
            (cell(seg).id == -1 or citizen(cell(seg).id).type == Builder) and
            citizen(cell(seg).id).player != me() and
            cell(seg).resistance == -1) {
          dist[seg.i][seg.j] = dist[act.i][act.j] + 1;

          if (seg == citizen(id).pos) found = true;
          q.push(seg);
        }
      }
    }

    int min = 34;
    Dir ret = dirs[random(0, 3)];
    for (int i = 0; i < 4; ++i) {
      Pos nou = (citizen(id).pos + dirs[i]);
      if (pos_ok(nou)) {
        if (dist[nou.i][nou.j] < min and dist[nou.i][nou.j] != -1) {
          min = dist[nou.i][nou.j];
          ret = dirs[i];
        }
      }
    }
    return ret;
  }

  ///////////////////// MOVIMENT JUGADORS////////////

  void builder_movement() {
    vector<int> bldrs = builders(me());
    vector<Pos> b = barricades(me());
    if (is_day()) {               // si es de dia
      if ((round() % 25) > 19) {  // construir barricades al final del dia
        if (b.size() < 3) {       // cal construir 3 barricades
          int i = 0;
          for (int id : bldrs) {
            if (i < 3) {
              Pos p = citizen(id).pos;
              bool found = false;
              int j = 0;
              while (not found and j < 4) {
                Dir d = dirs[j];
                if (pos_ok(p + d) and cell(p + d).id == -1 and
                    cell(p + d).type != Building and
                    cell(p + d).resistance == -1) {
                  found = true;
                  b.push_back(p + d);
                  build(id, d);
                }
                ++j;
              }
              ++i;
            } else {
              Pos q = bfs_money(id);
              if (q.i != -1 and q.j != -1) {
                Dir d = Calculate_path(id, q);
                move(id, d);
              } else {
                q = bfs_weapon(id);
                if (q.i != -1 and q.j != -1) {
                  Dir d = Calculate_path(id, q);
                  move(id, d);
                } else
                  move(id, dirs[random(0, 3)]);
              }
            }
          }
        } else {  // cal millorar barricades
          int i = 0;
          for (int id : bldrs) {
            if (i < 3) {
              Pos p = citizen(id).pos;
              for (int j = 0; j < 4; ++j) {
                Dir d = dirs[j];
                if (pos_ok(p + d) and cell(p + d).b_owner == me()) build(id, d);
              }
              ++i;
            } else {
              Pos q = bfs_money(id);
              if (q.i != -1 and q.j != -1) {
                Dir d = Calculate_path(id, q);
                move(id, d);
              } else {
                q = bfs_weapon(id);
                if (q.i != -1 and q.j != -1) {
                  Dir d = Calculate_path(id, q);
                  move(id, d);
                } else
                  move(id, dirs[random(0, 3)]);
              }
            }
          }
        }
      } else {  // principi del dia
        for (int id : bldrs) {
          Pos p;
          if (citizen(id).life <=
              builder_ini_life() /
                  4)  // si li falten 3/4 de la vida inicial -> menjar
            p = bfs_food(id);
          else {
            // sino -> diners
            p = bfs_money(id);
          }

          if (p.i != -1 and p.j != -1) {
            Dir d = Calculate_path(id, p);
            move(id, d);
          } else {
            p = bfs_weapon(id);
            if (p.i != -1 and p.j != -1) {
              Dir d = Calculate_path(id, p);
              move(id, d);
            } else
              move(id, dirs[random(0, 3)]);
          }
        }
      }
    } else {  // si es de nit
      for (int id : bldrs) {
        Pos p = citizen(id).pos;
        for (int i = 0; i < 4; ++i) {
          Dir d = dirs[i];
          if (pos_ok(p + d) and cell(p + d).b_owner == me() and
              cell(p + d).id == -1) {
            move(id, d);
            ++i;
          }
        }
        if ((round() % 25) >= 0 and
            cell(p).resistance ==
                -1) {  // al principi de la nit i no estic a una barricada
          Pos q = bfs_money(id);
          if (q.i != -1 and q.j != -1) {
            Dir d = Calculate_path(id, q);
            move(id, d);
          } else {
            q = bfs_attack_builders(id);
            if (q.i != -1 and q.j != -1) {
              Dir d = Path_for_builder(id, q);
              move(id, d);
            }
            /*
            else {
              bfs_escape(id);
              if (q.i != -1 and q.j != -1) {
                Dir d = Path_for_warriors(id, q);
                move(id, d);
              } else
                move(id, dirs[random(0, 3)]);
            }
            */
          }
        }
      }
    }
  }

  void warrior_movement() {
    vector<int> wrrs = warriors(me());
    for (int id : wrrs) {
      if (is_day()) {  // es de dia
        Pos p;
        if (citizen(id).life <=
            warrior_ini_life() /
                4)  // es de dia i tinc menys de 3/4 de vida ->menjar
          p = bfs_food(id);
        else  // sino per defecte -> armes p =
          p = bfs_weapon(id);

        if (p.i != -1 and p.j != -1) {
          Dir d = Calculate_path(id, p);
          move(id, d);
        } else {
          p = bfs_money(id);
          if (p.i != -1 and p.j != -1) {
            Dir d = Calculate_path(id, p);
            move(id, d);
          } else
            move(id, dirs[random(0, 3)]);
        }
      } else {  // es de nit
        Pos p;
        if (citizen(id).weapon ==
            Bazooka) {  // si tinc bazoka ataco als de pistola
          p = bfs_attack_hammer(id);
          if (p.i != -1 and p.j != -1) {
            Dir d = Path_for_hammer(id, p);
            move(id, d);
          } else {
            p = bfs_attack_gun(id);
            if (p.i != -1 and p.j != -1) {
              Dir d = Path_for_gun(id, p);
              move(id, d);
            } else {
              p = bfs_attack_bazooka(id);
              if (p.i != -1 and p.j != -1) {
                Dir d = Path_for_bazooka(id, p);
                move(id, d);
              } else {
                p = bfs_attack_builders(id);
                if (p.i != -1 and p.j != -1) {
                  Dir d = Path_for_builder(id, p);
                  move(id, d);
                } else
                  move(id, dirs[random(0, 3)]);
              }
            }
          }
        } else {
          p = bfs_weapon(id);
          if (p.i != -1 and p.j != -1) {
            Dir d = Calculate_path(id, p);
            move(id, d);
          } else {
            p = bfs_attack_hammer(id);
            if (p.i != -1 and p.j != -1) {
              Dir d = Path_for_hammer(id, p);
              move(id, d);
            } else {
              p = bfs_attack_builders(id);
              if (p.i != -1 and p.j != -1) {
                Dir d = Path_for_builder(id, p);
                move(id, d);
              } else
                move(id, dirs[random(0, 3)]);
            }
          }
        }
      }
    }
  }

  /**
   * Play method, invoked once per each round.
   */
  virtual void play() {
    builder_movement();
    warrior_movement();
  }
};

/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
