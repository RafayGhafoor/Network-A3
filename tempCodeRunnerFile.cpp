    for (int i = 0; tmp[i] && i < tmp.size(); i++)
      while (tmp[i])
      {
        addConnection(net[i], tmp[i]->id);
        tmp[i] = tmp[i]->next;
      }
