class VersionSet
{
  private:
    vector<FileMetaData*> files_[config::kNumLevels];
  public:
    bool Get(const Slice& key, Slice& value)
    {
      vector<int64_t> file_ids;
      for (int level = 0; level < config::kNumLevels; ++level)
      {
        size_t file_size = files_[level].size();
        if (file_size <= 0)
            continue;
        if (level == 0)
        {
          for (int i = 0; i < files_[level].size(); ++i)
          {
            if (key >= files_[level][i]->small_key && key <= files_[level][i]->max_key)
              file_ids.push_back(files_[level][i].file_id);
          }
        }
        else
        {
          if (file_id = FindFile(files_[level], key) != -1)
          {
            file_ids.push_back(file_id);
          }
        }
      }
      for (auto it = file_ids.begin(); it != file_ids.end(); ++it)
      {
        if (table_cache->Get(file_id, key, value))
        {
          return;
        }
      }
    }
};

