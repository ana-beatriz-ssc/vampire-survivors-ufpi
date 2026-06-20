#pragma once

// Stub intencional: mantém o módulo preparado sem adicionar dependência externa.
// Pode ser substituído por SDL2_mixer/OpenAL depois que o jogo estiver estável.
class Audio {
public:
    bool initialize();
    void playShot();
    void playEnemyDeath();
};
