#include <iostream>
#include <memory>
#include <string>
#include <vector>

// Real-world: Video Game Checkpoint / Save State System
class GameCharacter {
    int health_ = 100;
    int mana_ = 50;
    int level_ = 1;
    std::string checkpoint_name_ = "Spawn";

public:
    class SaveState {
        friend class GameCharacter;
        int health;
        int mana;
        int level;
        std::string checkpoint;
        SaveState(int h, int m, int l, std::string c)
            : health(h), mana(m), level(l), checkpoint(std::move(c)) {}
    };

    void take_damage(int dmg) { health_ -= dmg; }
    void level_up() { ++level_; health_ = 100; mana_ = 100; }
    void reach_checkpoint(std::string name) { checkpoint_name_ = std::move(name); }

    std::unique_ptr<SaveState> create_save() const {
        return std::unique_ptr<SaveState>(new SaveState(health_, mana_, level_, checkpoint_name_));
    }

    void load_save(const SaveState& state) {
        health_ = state.health;
        mana_ = state.mana;
        level_ = state.level;
        checkpoint_name_ = state.checkpoint;
    }

    void print_status() const {
        std::cout << "[Player Status] Checkpoint: " << checkpoint_name_
                  << ", Level: " << level_ << ", HP: " << health_ << ", Mana: " << mana_ << "\n";
    }
};

int main() {
    GameCharacter player;
    player.print_status();

    player.reach_checkpoint("Dragon Lair Entrance");
    player.level_up();
    auto save1 = player.create_save();
    player.print_status();

    std::cout << "\nFighting Boss...\n";
    player.take_damage(90);
    player.print_status();

    std::cout << "\nPlayer loading checkpoint save...\n";
    player.load_save(*save1);
    player.print_status();
    return 0;
}
