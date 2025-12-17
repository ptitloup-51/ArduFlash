# ArduFlash - Flash Trigger Arduino pour Godox V1C

Déclencheur de flash DIY pour contrôler un Godox V1C (ou tout autre flash compatible) via Arduino et un hot shoe imprimé en 3D.

![Version](https://img.shields.io/badge/version-1.0-blue)
![Arduino](https://img.shields.io/badge/Arduino-Due-00979D?logo=arduino)

## 📋 Table des matières

- [Présentation](#présentation)
- [Matériel nécessaire](#matériel-nécessaire)
- [Principe de fonctionnement](#principe-de-fonctionnement)
- [Réalisation du hot shoe](#réalisation-du-hot-shoe)
- [Schéma de câblage](#schéma-de-câblage)
- [Code Arduino](#code-arduino)
- [Installation](#installation)
- [Utilisation](#utilisation)

## 🎯 Présentation

Ce projet permet de déclencher automatiquement un flash Godox V1C (ou compatible) depuis une carte Arduino Due. L'isolation électrique est assurée par un optocoupleur pour protéger votre Arduino.


## 🛠️ Matériel nécessaire

### Électronique

| Composant | Quantité | 
|-----------|----------|
| **Arduino** | 1 |
| **Optocoupleur PC817** | 1 |
| **Résistance 220Ω** | 1 |
| **Fils de prototypage** | 5 |
| **Breadboard** (optionnel) | 1 |


### Hot shoe imprimé en 3D

| Composant | Quantité | Spécifications | 
|-----------|----------|----------------|
| **Fichier STL** | 1 | Hot shoe personnalisé |
| **Clous** | 2 | Diamètre du corps 1.5mm, diamètre de la tête 3mm |
| **Gaine thermorétractable** | 10cm | Diamètre 2-3mm |

### Outils

- Fer à souder
- Étain (avec flux)
- Pince coupante
- Briquet (gaine thermo)

## 🔍 Principe de fonctionnement

Le flash se déclenche en **court-circuitant momentanément** les deux contacts du hot shoe (trigger + masse). L'optocoupleur PC817 isole électriquement l'Arduino du circuit du flash, évitant tout risque de dommage.

```
Arduino → LED (optocoupleur) → Photorécepteur → Court-circuit hot shoe → Flash déclenché
```

**Pourquoi un optocoupleur ?**
- ✅ Isolation galvanique (sécurité)
- ✅ Protection de l'Arduino
- ✅ Aucun risque de retour de tension
- ✅ Compatible avec tous les flashs

## 🖨️ Réalisation du hot shoe

### Étape 1 : Impression 3D

1. Téléchargez le fichier `hot_shoe.stl` depuis ce repository
2. Imprimez avec les paramètres suivants :
   - **Matériau :** PLA
   - **Remplissage :** 15%
   - **Résolution :** 0.2mm
   - **Supports :** Oui

### Étape 2 : Installation des contacts

1. **Préparez les clous :**
   ```
   Clou original : ═══════════▸
   Après coupe :   ═══════│
   ```
   - Coupez la pointe du clou avec une pince coupante

2. **Insertion dans le hot shoe :**
   - Insérez les 2 clous dans les emplacements prévus à l'aide d'un marteau
   - **Position :** 
     - Clou 1 : Contact central (trigger/X-sync)
     - Clou 2 : Contact latéral (masse/GND)
   - Les clous ne doivent pas dépasser côté intérieur, il doivent être plaqués le plus possible

3. **Fixation (optionnel):**
   - Ajoutez une goutte de colle cyanoacrylate (Super Glue) coté éxterieur
   - Laissez sécher 5 minutes

### Étape 3 : Soudure des fils

1. **Préparez 2 fils :**
   - Dénudez à chaque extrémité
   - Étamez les extrémités

2. **Soudure sur les clous :**
   ```
   Clou → [Fil soudé] → [Gaine thermo] → Connexion Arduino
   ```
   - Soudez solidement sur chaque clou
   - faite attention à ne pas trop chauffer pour ne pas faire fondre le PLA

3. **Protection avec gaine thermorétractable :**
   - Glissez 2-3cm de gaine sur chaque soudure
   - Chauffez avec un briquet

## 🔌 Schéma de câblage

### Vue d'ensemble

```
┌─────────────────┐                  ┌──────────────┐
│  Arduino        │                  │   PC817      │
│                 │                  │   ┌────┐     │
│            Pin7 ├──[R 220Ω]──────→ │1  │●  ○│4    ├─────→ Clou 1 (Trigger)
│                 │                  │   │    │     │
│             GND ├─────────────────→│2  │○  ○│3    ├─────→ Clou 2 (GND)
│                 │                  │   └────┘     │
│  [USB Prog.]    │                  └──────────────┘
└─────────────────┘                          ↓
                                        Hot shoe → Flash
```

### Brochage PC817

```
Vue de dessus :
     ┌─────┐
  1  │●    │ 4
     │ PC  │      
  2  │ 817 │ 3
     └─────┘

Pin 1 : Anode (LED)        → Résistance 220Ω → Arduino Pin 7
Pin 2 : Cathode (LED)      → Arduino GND
Pin 3 : Émetteur           → Hot shoe GND (Clou 2)
Pin 4 : Collecteur         → Hot shoe Trigger (Clou 1)
```

### Câblage détaillé

| Arduino Due | → | Composant | → | Hot shoe 3D |
|-------------|---|-----------|---|-------------|
| Pin 7 | → | Résistance 220Ω | → | PC817 Pin 1 | - |
| GND | → | - | → | PC817 Pin 2 | - |
| - | - | PC817 Pin 4 | → | Clou 1 (centre) |
| - | - | PC817 Pin 3 | → | Clou 2 (masse) |



### Photo du montage (à ajouter)

_[TODO: Ajoutez ici une photo de votre montage réel]_

## 💻 Code Arduino

### Code de base

```cpp
/*
  Flash Trigger pour Godox V1C
  Compatible Arduino Due
  
  Déclenche le flash en shuntant les contacts du hot shoe
  via un optocoupleur PC817 pour isolation galvanique.
  
  Auteur: Votre Nom
  Date: 2024
  License: MIT
*/

// Configuration des pins
const int FLASH_PIN = 7;           // Pin de commande du flash
const int PULSE_DURATION = 10;     // Durée de l'impulsion en ms
const int RECYCLE_TIME = 2000;     // Temps de recyclage du flash en ms

void setup() {
  // Initialisation du pin de commande
  pinMode(FLASH_PIN, OUTPUT);
  digitalWrite(FLASH_PIN, LOW);
  
  // Communication série pour debug
  Serial.begin(115200);
  Serial.println("=================================");
  Serial.println("Flash Trigger - Godox V1C");
  Serial.println("=================================");
  Serial.println("Pret a declencher !");
  Serial.println();
}

void loop() {
  // Déclenche le flash
  triggerFlash();
  
  // Affiche le statut
  Serial.println("Flash declenche !");
  
  // Attend le temps de recyclage
  delay(RECYCLE_TIME);
}

/**
 * Fonction de déclenchement du flash
 * Envoie une impulsion courte pour shunter les contacts
 */
void triggerFlash() {
  digitalWrite(FLASH_PIN, HIGH);   // Active le circuit
  delay(PULSE_DURATION);           // Maintient 10ms
  digitalWrite(FLASH_PIN, LOW);    // Désactive
}
```


## 📦 Installation

### 1. Préparation de l'environnement

1. **Téléchargez Arduino IDE** : https://www.arduino.cc/en/software
2. **Installez le support Arduino Due (si vous utilisez une carte Due)** :
   - Outils → Type de carte → Gestionnaire de cartes
   - Recherchez "SAM Boards (32-bits ARM Cortex-M3)"
   - Installez "Arduino SAM Boards"

### 2. Configuration de la carte

```
Outils → Type de carte → Arduino Due (Programming Port)
Outils → Port → [Sélectionnez votre port COM]
```

### 3. Upload du code

1. Copiez le code dans l'IDE Arduino
2. Vérifiez la compilation : `Ctrl+R` ou ✓
3. Téléversez vers la carte : `Ctrl+U` ou →

## 🚀 Utilisation

### Premier test

1. **Montez le flash** sur le hot shoe imprimé
2. **Réglez le flash en mode MANUEL** (M)
3. **Choisissez une puissance**
4. **Alimentez l'Arduino** via USB
5. **Observez** le flash se déclencher

---

**Version:** 1.0  
**Dernière mise à jour:** Décembre 2025
