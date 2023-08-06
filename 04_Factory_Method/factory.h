
#pragma once

#include <map>
#include <utility>

/**
 * @class Factory
 * @brief Implements a Factory design pattern with Register and Create methods
 *
 * The objects created by this factory all implement the same interface
 * (namely, AbstractProduct). This design pattern is useful in settings where
 * multiple implementations of an interface are available, and one wishes to
 * defer the choice of the implementation in use.
 *
 * @param IdentifierType Type used for identifying the registered classes,
 * typically std::string.
 * @param AbstractProduct The interface implemented by the registered classes
 * @param ProductCreator Function returning a pointer to an instance of
 * the registered class
 * @param MapContainer Internal implementation of the function mapping
 * IdentifierType to ProductCreator, by default std::unordered_map
 */
template <typename IdentifierType, class AbstractProduct,
          class ProductCreator = AbstractProduct *(*)(),
          class MapContainer = std::map<IdentifierType, ProductCreator>>
class Factory {
 public:
  /**
   * @brief Registers the class given by the creator function, linking it to id.
   * Registration must happen prior to calling CreateObject.
   * @param id Identifier of the class being registered
   * @param creator Function returning a pointer to an instance of
   * the registered class
   * @return True if the key id is still available
   */
  bool Register(const IdentifierType &id, ProductCreator creator) {
    return producers_.insert(std::make_pair(id, creator)).second;
  }

  bool Contains(const IdentifierType &id) {
    return producers_.find(id) != producers_.end();
  }

  /**
   * @brief Unregisters the class with the given identifier
   * @param id The identifier of the class to be unregistered
   */
  bool Unregister(const IdentifierType &id) {
    return producers_.erase(id) == 1;
  }

  void Clear() { producers_.clear(); }

  bool Empty() const { return producers_.empty(); }

  /**
   * @brief Creates and transfers membership of an object of type matching id.
   * Need to register id before CreateObject is called. May return nullptr
   * silently.
   * @param id The identifier of the class we which to instantiate
   * @param args the object construction arguments
   */
  template <typename... Args>
  AbstractProduct* CreateObjectOrNull(const IdentifierType &id,
                                      Args &&... args) {
    auto id_iter = producers_.find(id);
    if (id_iter != producers_.end()) {
      return (id_iter->second)(std::forward<Args>(args)...);
    }
    return nullptr;
  }

  /**
   * @brief Creates and transfers membership of an object of type matching id.
   * Need to register id before CreateObject is called.
   * @param id The identifier of the class we which to instantiate
   * @param args the object construction arguments
   */
  template <typename... Args>
  AbstractProduct* CreateObject(const IdentifierType &id,
                                Args &&... args) {
    auto result = CreateObjectOrNull(id, std::forward<Args>(args)...);
    // std::cout << "Factory could not create Object of type : " << id;
    return result;
  }

  const MapContainer& Map() {
    return producers_;
  }

 private:
  MapContainer producers_;
};