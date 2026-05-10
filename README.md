# LAB 23 — JNI + Protection Anti-Debug Native

## Description

Ce laboratoire étend le projet JNI précédent en ajoutant une **couche de sécurité native en C++** permettant de détecter certains environnements suspects comme le debug ou l'instrumentation dynamique.

L'application utilise :
- **Java** pour l'interface Android,
- **C++** pour les contrôles de sécurité,
- **JNI** pour la communication Java ↔ C++,
- **NDK** et **CMake** pour la compilation native.

---

## Technologies utilisées

| Technologie | Rôle |
|---|---|
| Android Studio | IDE de développement |
| Java | Interface Android |
| C++ | Contrôles de sécurité natifs |
| JNI | Pont Java ↔ C++ |
| Android NDK | Compilation native |
| CMake | Système de build natif |

---

## Fonctionnalités

- ✅ Détection anti-debug avec `ptrace`
- ✅ Inspection de `/proc/self/maps`
- ✅ Communication JNI sécurisée
- ✅ Blocage logique des fonctions natives
- ✅ Logs natifs dans Logcat

---

## Architecture du projet

```text
app
 └── src/main
      ├── cpp
      │    ├── jnidemo.cpp
      │    └── CMakeLists.txt
      │
      ├── java/com.example.jnidemo
      │    └── MainActivity.java
      │
      └── res/layout
           └── activity_main.xml
```

---

## Résultats attendus

### Mode sécurisé

```
✅ Environnement sécurisé
JNI sécurisé : Java communique avec C++
Factoriel de 10 = 3628800
```

### Mode suspect

```
⚠ Environnement suspect détecté
Fonction JNI protégée
Calcul natif désactivé
```
<img width="738" height="1600" alt="image" src="https://github.com/user-attachments/assets/d7d08e17-1f1a-4aba-9dad-4a438465e73a" />

---

## Conclusion

Ce laboratoire montre comment Android peut utiliser **JNI** et le **NDK** pour intégrer des contrôles de sécurité natifs et protéger certaines fonctionnalités sensibles contre le debug et l'instrumentation dynamique.

---

## Auteur
Nom:Ouirouane Hiba

> Projet réalisé dans le cadre du cours : **Programmation Mobile — Android avec Java**
