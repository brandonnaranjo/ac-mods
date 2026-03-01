@interface ViewController () <UISearchBarDelegate>

@property (nonatomic, strong) UIButton *minimizeButton;
@property (nonatomic, strong) UIButton *maximizeButton;
@property (nonatomic, assign) CGRect originalFrame; // Stores original GUI size

@property (nonatomic, strong) UIScrollView *categoryScrollView;
@property (nonatomic, strong) UIScrollView *itemsScrollView;
@property (nonatomic, strong) UILabel *infoLabel;
@property (nonatomic, strong) UISearchBar *searchBar;

@property (nonatomic, strong) NSMutableArray<NSString *> *categories;
@property (nonatomic, strong) NSMutableArray<NSNumber *> *filteredIndexes;

@property (nonatomic, strong) NSString *selectedCategory;
@property (nonatomic, strong) NSString *searchText;

@end

// Simplified item structure
typedef struct {
    const char *id;
    int netID;
    const char *name;
    const char *category;
} Item;

// All items array (same as provided)
Item items[] = {
    { "item_apple", 71, "Apple", "Consumables" },
    { "item_arrow", 103, "Arrow", "Ammo" },
    { "item_arrow_heart", 116, "Heart Arrow", "Ammo" },
    { "item_arrow_lightbulb", 105, "Lightbulb Arrow", "Ammo" },
    { "item_backpack", 1, "Backpack", "Bags" },
    { "item_backpack_black", 2, "Black Backpack", "Hidden" },
    { "item_backpack_green", 3, "Green Backpack", "Hidden" },
    { "item_backpack_large_base", 88, "Large Backpack", "Bags" },
    { "item_backpack_large_basketball", 138, "Large Basketball Print Backpack", "Bags" },
    { "item_backpack_large_clover", 137, "Large Clover Print Backpack", "Bags" },
    { "item_backpack_pink", 4, "Pink Backpack", "Hidden" },
    { "item_backpack_small_base", 87, "Small Backpack", "Bags" },
    { "item_backpack_white", 5, "White Backpack", "Hidden" },
    { "item_backpack_with_flashlight", 6, "Backpack with Flashlight", "Hidden" },
    { "item_balloon", 75, "Balloon", "Toys" },
    { "item_balloon_heart", 115, "Heart Balloon", "Toys" },
    { "item_banana", 23, "Banana", "Hidden" },
    { "item_baseball_bat", 63, "Baseball Bat", "Weapons" },
    { "item_big_cup", 38, "Big Cup", "Hidden" },
    { "item_boombox", 7, "Boombox", "Gadgets" },
    { "item_box_fan", 122, "Box Fan", "Gadgets" },
    { "item_calculator", 126, "Calculator", "Loot" },
    { "item_cardboard_box", 145, "Cardboard Box", "Hidden" },
    { "item_cash", 49, "Cash", "Hidden" },
    { "item_cash_mega_pile", 51, "Cash Mega Pile", "Hidden" },
    { "item_cash_pile", 50, "Cash Pile", "Hidden" },
    { "item_clapper", 78, "Clapper", "Toys" },
    { "item_cluster_grenade", 80, "Cluster Grenade", "Explosives" },
    { "item_cola", 25, "Cola", "Hidden" },
    { "item_cola_large", 26, "Large Cola", "Hidden" },
    { "item_company_ration", 67, "Company Ration", "Consumables" },
    { "item_company_ration_heal", 121, "Company Ration", "Consumables" },
    { "item_cracker", 72, "Cracker", "Consumables" },
    { "item_crate", 8, "Crate", "Hidden" },
    { "item_crossbow", 9, "Crossbow", "Weapons" },
    { "item_crossbow_heart", 117, "Heart Crossbow", "Weapons" },
    { "item_crowbar", 10, "Crowbar", "Weapons" },
    { "item_disc", 127, "DVD", "Loot" },
    { "item_disposable_camera", 11, "Disposable Camera", "Gadgets" },
    { "item_dynamite", 83, "Dynamite", "Explosives" },
    { "item_dynamite_cube", 143, "Cube Dynamite", "Explosives" },
    { "item_egg", 27, "Egg", "Hidden" },
    { "item_flaregun", 12, "Flaregun", "Weapons" },
    { "item_flashbang", 13, "Flashbang", "Explosives" },
    { "item_flashlight", 14, "Flashlight", "Gadgets" },
    { "item_flashlight_mega", 15, "Mega Flashlight", "Gadgets" },
    { "item_flashlight_red", 55, "Red Flashlight", "Hidden" },
    { "item_floppy3", 128, "Floppy Disc", "Loot" },
    { "item_floppy5", 129, "Floppy Disc", "Loot" },
    { "item_football", 62, "Football", "Toys" },
    { "item_frying_pan", 64, "Frying Pan", "Weapons" },
    { "item_glowstick", 79, "Glowstick", "Gadgets" },
    { "item_goldbar", 28, "Gold Bar", "Hidden" },
    { "item_grenade", 16, "Impact Grenade", "Explosives" },
    { "item_heart_chunk", 48, "Heart Chunk", "Hidden" },
    { "item_heart_gun", 54, "Heart Gun", "Weapons" },
    { "item_heartchocolatebox", 114, "Heart Chocolate Box", "Consumables" },
    { "item_hh_key", 29, "Haunted House Key", "Hidden" },
    { "item_hookshot", 82, "Hookshot", "Gadgets" },
    { "item_hoverpad", 30, "Hoverpad", "Gadgets" },
    { "item_impulse_grenade", 89, "Impulse Grenade", "Explosives" },
    { "item_jetpack", 17, "Jetpack", "Gadgets" },
    { "item_keycard", 125, "Keycard", "Loot" },
    { "item_lance", 74, "Lance", "Weapons" },
    { "item_large_banana", 24, "Large Banana", "Hidden" },
    { "item_mug", 130, "Mug", "Loot" },
    { "item_nut", 31, "Nut", "Hidden" },
    { "item_ogre_hands", 66, "Ogre Hands", "Weapons" },
    { "item_ore_copper_l", 95, "Large Copper Chunk", "Loot" },
    { "item_ore_copper_m", 94, "Copper Chunk", "Loot" },
    { "item_ore_copper_s", 93, "Small Copper Chunk", "Loot" },
    { "item_ore_gold_l", 101, "Large Gold Chunk", "Loot" },
    { "item_ore_gold_m", 100, "Gold Chunk", "Loot" },
    { "item_ore_gold_s", 99, "Small Gold Chunk", "Loot" },
    { "item_ore_hell", 113, "Cinder", "Loot" },
    { "item_ore_silver_l", 98, "Large Silver Chunk", "Loot" },
    { "item_ore_silver_m", 97, "Small Silver Chunk", "Loot" },
    { "item_ore_silver_s", 96, "Silver Chunk", "Loot" },
    { "item_painting_canvas", 52, "Painting Canvas", "Hidden" },
    { "item_paperpack", 131, "Paper", "Loot" },
    { "item_pelican_case", 32, "Black Crate", "Hidden" },
    { "item_pickaxe", 65, "Pickaxe", "Weapons" },
    { "item_pickaxe_cny", 108, "Golded Pickaxe", "Weapons" },
    { "item_pickaxe_cube", 142, "Cube Pickaxe", "Weapons" },
    { "item_pipe", 33, "Pipe", "Hidden" },
    { "item_plunger", 34, "Plunger", "Gadgets" },
    { "item_pogostick", 35, "Pogostick", "Toys" },
    { "item_police_baton", 124, "Police Baton (Crowbar)", "Weapons" },
    { "item_pumpkin_pie", 73, "Pumpkin Pie", "Consumables" },
    { "item_pumpkinjack", 56, "Pumpkin Jack", "Hidden" },
    { "item_pumpkinjack_small", 57, "Small Pumpkin Jack", "Hidden" },
    { "item_quiver", 104, "Quiver", "Bags" },
    { "item_quiver_heart", 118, "Heart Quiver", "Bags" },
    { "item_radioactive_broccoli", 119, "Mega Broccoli", "Consumables" },
    { "item_randombox_mobloot_big", 58, "Big Mob Loot Box", "Hidden" },
    { "item_randombox_mobloot_medium", 59, "Mob Loot Box", "Hidden" },
    { "item_randombox_mobloot_small", 60, "Small Mob Loot Box", "Hidden" },
    { "item_randombox_mobloot_weapons", 92, "Mob Weapons Loot Box", "Loot" },
    { "item_revolver", 68, "Revolver", "Weapons" },
    { "item_revolver_ammo", 86, "Revolver Ammo", "Ammo" },
    { "item_rope", 112, "Rope", "Ammo" },
    { "item_rpg", 84, "RPG", "Weapons" },
    { "item_rpg_ammo", 85, "RPG Rocket", "Ammo" },
    { "item_rpg_cny", 110, "Rocket Dragon RPG", "Weapons" },
    { "item_rubberducky", 36, "Rubber Ducky", "Toys" },
    { "item_ruby", 37, "Ruby", "Hidden" },
    { "item_saddle", 61, "Saddle", "Gadgets" },
    { "item_scanner", 18, "Scanner", "Hidden" },
    { "item_scissors", 132, "Scissors", "Loot" },
    { "item_shield", 77, "Shield", "Weapons" },
    { "item_shield_bones", 109, "Protective Bone Shield", "Weapons" },
    { "item_shield_police", 123, "Police Shield", "Weapons" },
    { "item_shotgun", 19, "Shotgun", "Weapons" },
    { "item_shotgun_ammo", 20, "Shotgun Ammo", "Ammo" },
    { "item_shredder", 135, "Nut Shredder", "Bags" },
    { "item_shrinking_broccoli", 120, "Micro Broccoli", "Consumables" },
    { "item_snowball", 91, "Snowball", "Weapons" },
    { "item_stapler", 133, "Stapler", "Loot" },
    { "item_stick_armbones", 107, "Arm Bones (Stick)", "Weapons" },
    { "item_stick_bone", 106, "Bone (Stick)", "Weapons" },
    { "item_sticker_dispenser", 144, "Sticker Dispenser", "Gadgets" },
    { "item_sticky_dynamite", 102, "Sticky Dynamite", "Explosives" },
    { "item_stinky_cheese", 140, "Stinky Cheese", "Consumables" },
    { "item_tablet", 21, "Tablet", "Gadgets" },
    { "item_tapedispenser", 134, "Tape Dispenser", "Loot" },
    { "item_tele_grenade", 76, "Tele Grenade", "Gadgets" },
    { "item_theremin", 136, "Theremin", "Toys" },
    { "item_timebomb", 141, "Time Bomb", "Loot" },
    { "item_toilet_paper", 39, "Toilet Paper", "Hidden" },
    { "item_toilet_paper_mega", 41, "Mega Toilet Paper", "Hidden" },
    { "item_toilet_paper_roll_empty", 40, "Empty Toilet Paper Roll", "Hidden" },
    { "item_treestick", 90, "Tree Stick", "Weapons" },
    { "item_tripwire_explosive", 22, "Tripwire Explosive", "Explosives" },
    { "item_trophy", 42, "Trophy", "Hidden" },
    { "item_turkey_leg", 70, "Turkey Leg", "Consumables" },
    { "item_turkey_whole", 69, "Turkey Whole", "Consumables" },
    { "item_umbrella", 43, "Umbrella", "Gadgets" },
    { "item_umbrella_clover", 139, "Clover Umbrella", "Gadgets" },
    { "item_unidentified", 0, "Unknown Item", "Hidden" },
    { "item_upsidedown_loot", 53, "Upsidedown Loot", "Hidden" },
    { "item_uranium_chunk_l", 46, "Large Uranium Chunk", "Hidden" },
    { "item_uranium_chunk_m", 45, "Uranium Chunk", "Hidden" },
    { "item_uranium_chunk_s", 44, "Small Uranium Chunk", "Hidden" },
    { "item_whoopie", 47, "Whoopie", "Toys" },
};
int itemsCount = sizeof(items)/sizeof(Item);

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];

    UIImageView *backgroundImageView = [[UIImageView alloc] initWithFrame:self.view.bounds];
    backgroundImageView.image = [UIImage imageNamed:@"Gojo_Gui.png"]; // Add this image to your project
    backgroundImageView.contentMode = UIViewContentModeScaleAspectFill;
    [self.view addSubview:backgroundImageView];
    [self.view sendSubviewToBack:backgroundImageView]; // Make sure it's behind other views
    
        // Calculate 8% size of the view width
    CGFloat buttonSize = self.view.frame.size.width * 0.08;

    // Minimize button (top-right)
    self.minimizeButton = [UIButton buttonWithType:UIButtonTypeCustom];
    self.minimizeButton.frame = CGRectMake(self.view.frame.size.width - buttonSize - 10, 40, buttonSize, buttonSize);
    [self.minimizeButton setImage:[UIImage imageNamed:@"minimize.png"] forState:UIControlStateNormal]; // your image
    self.minimizeButton.imageView.contentMode = UIViewContentModeScaleAspectFit;
    [self.minimizeButton addTarget:self action:@selector(minimizeGUI) forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:self.minimizeButton];

    self.minimizeButton.layer.cornerRadius = buttonSize / 2;
    self.minimizeButton.clipsToBounds = YES;

    // Maximize button (top-right, hidden initially)
    self.maximizeButton = [UIButton buttonWithType:UIButtonTypeCustom];
    self.maximizeButton.frame = CGRectMake(self.view.frame.size.width - buttonSize - 10, 40, buttonSize, buttonSize);
    [self.maximizeButton setImage:[UIImage imageNamed:@"maximize.png"] forState:UIControlStateNormal]; // your image
    self.maximizeButton.imageView.contentMode = UIViewContentModeScaleAspectFit;
    self.maximizeButton.hidden = YES;
    [self.maximizeButton addTarget:self action:@selector(maximizeGUI) forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:self.maximizeButton];

    self.maximizeButton.layer.cornerRadius = buttonSize / 2;
    self.maximizeButton.clipsToBounds = YES;

    // Store original GUI frame
    self.originalFrame = self.view.frame;

    // Title
    UILabel *titleLabel = [[UILabel alloc] initWithFrame:CGRectMake(0, 50, self.view.frame.size.width, 50)];
    titleLabel.text = @"The Honored One";
    titleLabel.textColor = [UIColor colorWithRed:0.53 green:0.81 blue:0.98 alpha:1.0];
    titleLabel.textAlignment = NSTextAlignmentCenter;
    titleLabel.font = [UIFont boldSystemFontOfSize:32];
    [self.view addSubview:titleLabel];
    
    // Extract categories
    [self extractCategories];
    
    // Category Scroll
    self.categoryScrollView = [[UIScrollView alloc] initWithFrame:CGRectMake(0, 110, self.view.frame.size.width, 50)];
    [self.view addSubview:self.categoryScrollView];
    [self buildCategoryButtons];
    
    // Search Bar
    self.searchBar = [[UISearchBar alloc] initWithFrame:CGRectMake(20, 170, self.view.frame.size.width - 40, 40)];
    self.searchBar.delegate = self;
    self.searchBar.placeholder = @"Search items...";
    [self.view addSubview:self.searchBar];
    
    // Info Label
    CGFloat infoHeight = 200;
    self.infoLabel = [[UILabel alloc] initWithFrame:CGRectMake(20, self.view.frame.size.height - infoHeight, self.view.frame.size.width - 40, infoHeight)];
    self.infoLabel.textColor = [UIColor whiteColor];
    self.infoLabel.numberOfLines = 0;
    [self.view addSubview:self.infoLabel];
    
    // Items Scroll
    CGFloat itemsY = CGRectGetMaxY(self.searchBar.frame) + 10;
    CGFloat itemsHeight = CGRectGetMinY(self.infoLabel.frame) - itemsY - 10;
    self.itemsScrollView = [[UIScrollView alloc] initWithFrame:CGRectMake(20, itemsY, self.view.frame.size.width - 40, itemsHeight)];
    self.itemsScrollView.backgroundColor = [UIColor colorWithWhite:0.2 alpha:1.0];
    self.itemsScrollView.contentInset = UIEdgeInsetsMake(0, 0, 10, 0);
    [self.view addSubview:self.itemsScrollView];
    
    // Default filter & search
    self.selectedCategory = @"All";
    self.searchText = @"";
    [self applyFilters];
}

#pragma mark - Category Setup

- (void)extractCategories {
    self.categories = [NSMutableArray array];
    [self.categories addObject:@"All"];
    
    for (int i = 0; i < itemsCount; i++) {
        NSString *cat = [NSString stringWithUTF8String:items[i].category];
        if (![self.categories containsObject:cat]) {
            [self.categories addObject:cat];
        }
    }
}

- (void)buildCategoryButtons {
    CGFloat xOffset = 10;
    
    for (int i = 0; i < self.categories.count; i++) {
        UIButton *button = [UIButton buttonWithType:UIButtonTypeSystem];
        button.frame = CGRectMake(xOffset, 5, 120, 40);
        [button setTitle:self.categories[i] forState:UIControlStateNormal];
        [button setTitleColor:[UIColor blackColor] forState:UIControlStateNormal];
        button.backgroundColor = [UIColor colorWithRed:0.53 green:0.81 blue:0.98 alpha:1.0];
        button.layer.cornerRadius = 8;
        button.tag = i;
        [button addTarget:self action:@selector(categoryTapped:) forControlEvents:UIControlEventTouchUpInside];
        [self.categoryScrollView addSubview:button];
        xOffset += 130;
    }
    self.categoryScrollView.contentSize = CGSizeMake(xOffset, 50);
}

#pragma mark - Filtering

- (void)categoryTapped:(UIButton *)sender {
    self.selectedCategory = self.categories[sender.tag];
    [self applyFilters];
}

- (void)applyFilters {
    self.filteredIndexes = [NSMutableArray array];
    
    for (int i = 0; i < itemsCount; i++) {
        NSString *itemName = [NSString stringWithUTF8String:items[i].name];
        NSString *itemCategory = [NSString stringWithUTF8String:items[i].category];
        
        BOOL matchesCategory = [self.selectedCategory isEqualToString:@"All"] || [itemCategory isEqualToString:self.selectedCategory];
        BOOL matchesSearch = self.searchText.length == 0 || [[itemName lowercaseString] containsString:[self.searchText lowercaseString]];
        
        if (matchesCategory && matchesSearch) {
            [self.filteredIndexes addObject:@(i)];
        }
    }
    
    [self rebuildItemButtons];
}

#pragma mark - Item Buttons

- (void)rebuildItemButtons {
    for (UIView *subview in self.itemsScrollView.subviews) {
        [subview removeFromSuperview];
    }
    
    CGFloat buttonHeight = 50;
    CGFloat spacing = 10;
    
    for (int i = 0; i < self.filteredIndexes.count; i++) {
        int idx = [self.filteredIndexes[i] intValue];
        
        UIButton *button = [UIButton buttonWithType:UIButtonTypeSystem];
        button.frame = CGRectMake(0, i*(buttonHeight+spacing), self.itemsScrollView.frame.size.width, buttonHeight);
        [button setTitle:[NSString stringWithUTF8String:items[idx].name] forState:UIControlStateNormal];
        [button setTitleColor:[UIColor yellowColor] forState:UIControlStateNormal];
        button.backgroundColor = [UIColor blackColor];
        button.layer.cornerRadius = 8;
        button.tag = idx;
        [button addTarget:self action:@selector(itemButtonTapped:) forControlEvents:UIControlEventTouchUpInside];
        
        [self.itemsScrollView addSubview:button];
    }
    
    self.itemsScrollView.contentSize = CGSizeMake(self.itemsScrollView.frame.size.width, self.filteredIndexes.count*(buttonHeight+spacing));
}

#pragma mark - Item Spawn

- (void)itemButtonTapped:(UIButton *)sender {
    int idx = (int)sender.tag;
    Item item = items[idx];
    
    self.infoLabel.text = [NSString stringWithFormat:@"Name: %s\nCategory: %s", item.name, item.category];
    
    NSLog(@"Spawned item: %s (netID: %d)", item.name, item.netID);
    // TODO: Add your spawn logic here
}

#pragma mark - Search

- (void)searchBar:(UISearchBar *)searchBar textDidChange:(NSString *)searchText {
    self.searchText = searchText;
    [self applyFilters];
}

- (void)searchBarSearchButtonClicked:(UISearchBar *)searchBar {
    [searchBar resignFirstResponder];
}

- (void)minimizeGUI {
    CGFloat buttonSize = self.view.frame.size.width * 0.08;

    [UIView animateWithDuration:0.3 animations:^{
        // Shrink entire GUI to small square at top-right
        self.view.frame = CGRectMake(self.view.frame.size.width - buttonSize - 10, 40, buttonSize, buttonSize);
    } completion:^(BOOL finished) {
        self.minimizeButton.hidden = YES;
        self.maximizeButton.hidden = NO;
    }];
}

- (void)maximizeGUI {
    [UIView animateWithDuration:0.3 animations:^{
        self.view.frame = self.originalFrame; // Restore original size
    } completion:^(BOOL finished) {
        self.minimizeButton.hidden = NO;
        self.maximizeButton.hidden = YES;
    }];
}

@end