auto dfs = [&](auto &&self, const std::string_view sv,
               const std::shared_ptr<const TrieNode> &node) -> std::shared_ptr<TrieNode> {
  auto new_node = std::shared_ptr<TrieNode>(std::move(node->Clone()));
  if (sv.empty()) {
    // 替换为带值的节点，并保留原有子节点
    if (new_node->is_value_node_) {
      if (auto value_node = std::dynamic_pointer_cast<TrieNodeWithValue<T>>(new_node)) {
        value_node->value_ = std::make_shared<T>(std::move(value));
        return value_node;
      }
    }
    return std::make_shared<TrieNodeWithValue<T>>(new_node->children_, std::make_shared<T>(std::move(value)));
  }

  const char c = sv.front();
  std::shared_ptr<const TrieNode> child;
  if (const auto it = node->children_.find(c); it != node->children_.end()) {
    child = it->second;
  } else {
    child = std::make_shared<TrieNode>();
  }

  new_node->children_[c] = self(self, sv.substr(1), child);
  return new_node;
};

return Trie{dfs(dfs, key, root_)};