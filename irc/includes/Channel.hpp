/* ************************************************************************** */
/*                                                                            */
/*   Channel.hpp - Represente un channel (salon) IRC                          */
/*                                                                            */
/*   Un channel possede :                                                     */
/*   - Une liste de membres (clients presents dans le channel)                */
/*   - Un set d'operateurs (membres avec privileges de gestion)               */
/*   - Un set d'invites (pour le mode invite-only)                            */
/*   - Des modes : i (invite-only), t (topic restreint aux ops),              */
/*     k (cle/mot de passe), l (limite de membres)                            */
/*                                                                            */
/*   Le premier client a rejoindre un channel en devient automatiquement      */
/*   l'operateur.                                                             */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <string>
#include <vector>
#include <set>

class Client;

class Channel {
public:
	Channel(const std::string& name);
	~Channel();

	/* --- Getters --- */
	const std::string& getName() const;
	const std::string& getTopic() const;
	const std::string& getKey() const;
	int getLimit() const;
	bool isInviteOnly() const;
	bool isTopicRestricted() const;
	bool hasKey() const;
	bool hasLimit() const;

	/* Retourne la string des modes actifs (ex: "+itk") pour la reponse MODE */
	std::string getModeString() const;

	/* --- Setters pour les modes --- */
	void setTopic(const std::string& topic);
	void setKey(const std::string& key);
	void removeKey();
	void setLimit(int limit);
	void removeLimit();
	void setInviteOnly(bool val);
	void setTopicRestricted(bool val);

	/* --- Gestion des membres --- */
	bool isMember(Client* c) const;
	bool isOperator(Client* c) const;
	bool isInvited(Client* c) const;
	void addMember(Client* c);

	/* Retire un membre du channel (le retire aussi des ops et invites) */
	void removeMember(Client* c);

	void addOperator(Client* c);
	void removeOperator(Client* c);
	void addInvited(Client* c);
	void removeInvited(Client* c);
	int memberCount() const;
	std::vector<Client*> getMembers() const;

	/*
	** Envoie un message a tous les membres du channel sauf 'exclude'.
	** Utilise queueMessage() sur chaque client pour respecter le mecanisme
	** de buffer d'envoi (les donnees seront envoyees quand POLLOUT est signale).
	** exclude est NULL pour envoyer a tout le monde (ex: JOIN, KICK).
	** exclude pointe vers l'emetteur pour PRIVMSG (on ne s'envoie pas son propre msg).
	*/
	void broadcast(const std::string& msg, Client* exclude);

private:
	std::string _name;               // Nom du channel (commence par #)
	std::string _topic;              // Topic actuel du channel
	std::string _key;                // Mot de passe du channel (mode +k)
	int _limit;                      // Limite de membres (mode +l), 0 = pas de limite
	bool _inviteOnly;                // Mode +i : seuls les invites peuvent rejoindre
	bool _topicRestricted;           // Mode +t : seuls les ops peuvent changer le topic
	std::vector<Client*> _members;   // Liste des membres du channel
	std::set<Client*> _operators;    // Set des operateurs du channel
	std::set<Client*> _invited;      // Set des clients invites (pour mode +i)
};

#endif
