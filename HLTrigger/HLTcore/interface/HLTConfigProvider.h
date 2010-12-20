#ifndef HLTcore_HLTConfigProvider_h
#define HLTcore_HLTConfigProvider_h

/** \class HLTConfigProvider
 *
 *  
 *  This class provides access routines to get hold of the HLT Configuration
 *
 *  $Date: 2010/12/17 14:42:37 $
 *  $Revision: 1.31 $
 *
 *  \author Martin Grunewald
 *
 */

#include <map>
#include <string>
#include <vector>


#include "L1Trigger/GlobalTriggerAnalyzer/interface/L1GtUtils.h"

#include "HLTrigger/HLTcore/interface/HLTConfigData.h"

#include "boost/shared_ptr.hpp"

#include<map>
#include<string>
#include<vector>


//
// class declaration
//
namespace edm {
  class Run;
  class Event;
  class LuminosityBlock;
  class ProcessHistory;
  class ParameterSet;
}

class HLTConfigProvider {

 public:
  /// Run-dependent initialisation (non-const method)
  ///   "init" return value indicates whether intitialisation has succeeded
  ///   "changed" parameter indicates whether the config has actually changed
  bool init(const edm::Run& iRun, const edm::EventSetup& iSetup,
	    const std::string& processName, bool& changed);

  /// Dumping config info to cout
  void dump(const std::string& what) const {
    hltConfigData_->dump(what);
  }

  /// Accessors (const methods)

  /// RunID
  const edm::RunID& runID() const {
    return runID_;
  }
  /// process name
  const std::string& processName() const {
    return processName_;
  }
  /// initialised?
  const bool inited() const {
    return inited_;
  }
  /// changed?
  const bool changed() const {
    return changed_;
  }

  /// number of trigger paths in trigger table
  unsigned int size() const {
    return hltConfigData_->size();
  }
  /// number of modules on a specific trigger path
  unsigned int size(unsigned int trigger) const {
    return hltConfigData_->size(trigger);
  }
  unsigned int size(const std::string& trigger) const {
    return hltConfigData_->size(trigger);
  }

  /// HLT ConfDB table name
  const std::string& tableName() const {
    return hltConfigData_->tableName();
  }

  /// names of trigger paths
  const std::vector<std::string>& triggerNames() const {
    return hltConfigData_->triggerNames();
  }
  const std::string& triggerName(unsigned int triggerIndex) const {
    return hltConfigData_->triggerName(triggerIndex);
  }

  /// slot position of trigger path in trigger table (0 to size-1)
  unsigned int triggerIndex(const std::string& triggerName) const {
    return hltConfigData_->triggerIndex(triggerName);
  }

  /// label(s) of module(s) on a trigger path
  const std::vector<std::string>& moduleLabels(unsigned int trigger) const {
    return hltConfigData_->moduleLabels(trigger);
  }
  const std::vector<std::string>& moduleLabels(const std::string& trigger) const {
    return hltConfigData_->moduleLabels(trigger);
  }
  const std::string& moduleLabel(unsigned int trigger, unsigned int module) const {
    return hltConfigData_->moduleLabel(trigger,module);
  }
  const std::string& moduleLabel(const std::string& trigger, unsigned int module) const {
    return hltConfigData_->moduleLabel(trigger,module);
  }

  /// slot position of module on trigger path (0 to size-1)
  unsigned int moduleIndex(unsigned int trigger, const std::string& module) const {
    return hltConfigData_->moduleIndex(trigger,module);
  }
  unsigned int moduleIndex(const std::string& trigger, const std::string& module) const {
    return hltConfigData_->moduleIndex(trigger,module);
  }

  /// C++ class name of module
  const std::string moduleType(const std::string& module) const {
    return hltConfigData_->moduleType(module);
  }

  /// ParameterSet of process
  const edm::ParameterSet& processPSet() const {
    return hltConfigData_->processPSet();
  }

  /// ParameterSet of module
  const edm::ParameterSet modulePSet(const std::string& module) const {
    return hltConfigData_->modulePSet(module);
  }


  /// HLTLevel1GTSeed module
  /// HLTLevel1GTSeed modules for all trigger paths
  const std::vector<std::vector<std::pair<bool,std::string> > >& hltL1GTSeeds() const {
    return hltConfigData_->hltL1GTSeeds();
  }
  /// HLTLevel1GTSeed modules for trigger path with name
  const std::vector<std::pair<bool,std::string> >& hltL1GTSeeds(const std::string& trigger) const {
    return hltConfigData_->hltL1GTSeeds(trigger);
  }
  /// HLTLevel1GTSeed modules for trigger path with index i
  const std::vector<std::pair<bool,std::string> >& hltL1GTSeeds(unsigned int trigger) const {
    return hltConfigData_->hltL1GTSeeds(trigger);
  }


  /// Streams
  /// list of names of all streams
  const std::vector<std::string>& streamNames() const {
    return hltConfigData_->streamNames();
  }
  /// name of stream with index i
  const std::string& streamName(unsigned int stream) const {
    return hltConfigData_->streamName(stream);
  }
  /// index of stream with name
  unsigned int streamIndex(const std::string& stream) const {
    return hltConfigData_->streamIndex(stream);
  }
  /// names of datasets for all streams
  const std::vector<std::vector<std::string> >& streamContents() const {
    return hltConfigData_->streamContents();
  }
  /// names of datasets in stream with index i
  const std::vector<std::string>& streamContent(unsigned int stream) const {
    return hltConfigData_->streamContent(stream);
  }
  /// names of datasets in stream with name
  const std::vector<std::string>& streamContent(const std::string& stream) const {
    return hltConfigData_->streamContent(stream);
  }


  /// Datasets
  /// list of names of all datasets
  const std::vector<std::string>& datasetNames() const {
    return hltConfigData_->datasetNames();
  }
  /// name of dataset with index i
  const std::string& datasetName(unsigned int dataset) const {
    return hltConfigData_->datasetName(dataset);
  }
  /// index of dataset with name
  unsigned int datasetIndex(const std::string& dataset) const {
    return hltConfigData_->datasetIndex(dataset);
  }
  /// names of trigger paths for all datasets
  const std::vector<std::vector<std::string> >& datasetContents() const {
    return hltConfigData_->datasetContents();
  }
  /// names of trigger paths in dataset with index i
  const std::vector<std::string>& datasetContent(unsigned int dataset) const {
    return hltConfigData_->datasetContent(dataset);
  }
  /// names of trigger paths in dataset with name
  const std::vector<std::string>& datasetContent(const std::string& dataset) const {
    return hltConfigData_->datasetContent(dataset);
  }


  /// HLT Prescales
  /// current (default) prescale set index - to be taken from L1GtUtil via Event
  int prescaleSet(const edm::Event& iEvent, const edm::EventSetup& iSetup) const;
  
  /// prescale value in specific prescale set for a specific trigger path
  unsigned int prescaleValue(unsigned int set, const std::string& trigger) const {
    return hltConfigData_->prescaleValue(set,trigger);
  }
  /// combining the two methods above
  unsigned int prescaleValue(const edm::Event& iEvent, const edm::EventSetup& iSetup, const std::string& trigger) const;
  
  /// Combined L1T (pair.first) and HLT (pair.second) prescales per HLT path
  std::pair<int,int> prescaleValues(const edm::Event& iEvent, const edm::EventSetup& iSetup, const std::string& trigger) const;

  // any one negative => error in retrieving this (L1T or HLT) prescale


  /// low-level data member access 
  unsigned int prescaleSize() const {
    return hltConfigData_->prescaleSize();
  }
  const std::vector<std::string>& prescaleLabels() const {
    return hltConfigData_->prescaleLabels();
  }
  const std::map<std::string,std::vector<unsigned int> >& prescaleTable() const {
    return hltConfigData_->prescaleTable();
  }


 public:
  /// c'tor
  HLTConfigProvider();
  
  /// d'tor
  ~HLTConfigProvider();
  
 private:
  void getDataFrom(const edm::ParameterSetID& iID, const std::string& iProcessName );
  void init(const edm::ProcessHistory& iHistory, const std::string& processName);
  void init(const std::string& processName);
  void clear();
  
  /// data members
  edm::RunID  runID_;
  std::string processName_;
  bool inited_;
  bool changed_;
  boost::shared_ptr<L1GtUtils> l1GtUtils_;
  const HLTConfigData* hltConfigData_;
  
};
#endif
